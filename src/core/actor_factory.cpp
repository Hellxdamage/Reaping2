#include "platform/i_platform.h"
#include "core/actor_factory.h"
#include "core/property_loader.h"
#include "core/i_renderable_component.h"
#include "component.h"

ActorFactory::ActorFactory()
{
    Init();
    //every created actor is handled the same way.
    //actorCreators create actors from json data files.
    Bind( AutoId( "default_actor" ), boost::bind( &ActorFactory::CreateActor, this, _1 ) );
    SetDefault( AutoId( "default_actor" ) );
}

std::auto_ptr<Actor> ActorFactory::CreateActor( int32_t Id )
{
    ActorCreatorMap_t::iterator i = mActorCreators.find( Id );
    return ( i != mActorCreators.end() ) ? i->second->Create() : std::auto_ptr<Actor>( new Actor( Id ) );
}


bool ActorFactory::AddActorCreatorFromOneDesc( Json::Value& ActorsDesc, ActorCreatorMap_t& actorCreators )
{
    std::auto_ptr<ActorCreator> actorCreator( new ActorCreator() );
    std::string nameStr;
    if( !Json::GetStr( ActorsDesc["name"], nameStr ) )
    {
        return false;
    }
    actorCreator->SetId( AutoId( nameStr ) );
    Json::Value& components = ActorsDesc["components"];
    if ( !components.isArray() )
    {
        return false;
    }
    if ( components.empty() )
    {
        return true;
    }
    for( Json::Value::iterator i = components.begin(), e = components.end(); i != e; ++i )
    {
        Json::Value& component = *i;
        std::string compName;
        if ( !Json::GetStr( component["name"], compName ) )
        {
            return false;
        }
        Json::Value& setters = component["set"];
        actorCreator->AddComponent( AutoId( compName ), setters );
    }
    int32_t actorCreatorId = actorCreator->GetId();
    actorCreators.insert( actorCreatorId, actorCreator );
    return true;
}

void ActorFactory::Init()
{
    PathVect_t Paths;
    Filesys& FSys = Filesys::Get();
    FSys.GetFileNames( Paths, "actors" );
    for( auto const& Path : Paths )
    {
        if( Path.extension().string() != ".actor" )
        {
            continue;
        }
        AutoFile JsonFile = FSys.Open( Path );
        if( !JsonFile.get() )
        {
            continue;
        }
        JsonReader Reader( *JsonFile );
        if( !Reader.IsValid() )
        {
            continue;
        }
        Json::Value Root = Reader.GetRoot();
        if( !Root.isArray() )
        {
            continue;
        }
        for( auto& ActorsDesc : Root )
        {
            try
            {
                if( !AddActorCreatorFromOneDesc( ActorsDesc, mActorCreators ) )
                {
                    return;
                }
            }
            catch( std::exception const& err )
            {
                L1( "Exception caught while parsing %s : %s", Path.generic_string().c_str(), err.what() );
            }
        }
    }
}

void ActorCreator::SetId( int32_t id )
{
    mId = id;
}

int32_t ActorCreator::GetId()
{
    return mId;
}

void ActorCreator::AddComponent( int32_t componentId, Json::Value& setters )
{
    std::auto_ptr<PropertyLoaderBase<Component> > compLoader = mComponentLoaderFactory( componentId );
    if( setters.isArray() && !setters.empty() )
    {
        compLoader->Load( *setters.begin() );
    }

    mComponentLoaders.insert( componentId, static_cast<ComponentLoader_t*>( compLoader.release() ) );
}

std::auto_ptr<Actor> ActorCreator::Create()const
{
    std::auto_ptr<Actor> actor( new Actor( mId ) );
    for( ComponentLoaderMap_t::const_iterator i = mComponentLoaders.begin(), e = mComponentLoaders.end(); i != e; ++i )
    {
        //        actor->AddComponent(i->second->FillProperties(mComponentFactory(i->first)));
        actor->AddComponent( mComponentFactory( i->first ) );
        i->second->FillProperties( *actor.get() );
    }
    //TODO: guid will come from outside zorder will be done by ordering at renderer
    Opt<IRenderableComponent> renderableC = actor->Get<IRenderableComponent>();
    if ( renderableC.IsValid() )
    {
        renderableC->SetZOrder( actor->GetGUID() );
    }
    return actor;
}

ActorCreator::ActorCreator()
    : mComponentFactory( ComponentFactory::Get() )
    , mComponentLoaderFactory( ComponentLoaderFactory::Get() )
    , mId( -1 )
{

}

