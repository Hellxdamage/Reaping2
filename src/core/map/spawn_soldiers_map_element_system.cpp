#include "platform/i_platform.h"
#include "spawn_soldiers_map_element_system.h"
#include "core/map/spawn_soldiers_map_element.h"
#include "engine/soldier_spawn_system.h"
#include "../player_controller_component.h"

namespace map {

SpawnSoldiersMapElementSystem::SpawnSoldiersMapElementSystem()
    : MapElementSystem()
    , mProgramState(core::ProgramState::Get())
{
}


void SpawnSoldiersMapElementSystem::Init()
{
    MapElementSystem::Init();
}


void SpawnSoldiersMapElementSystem::Update(double DeltaTime)
{
    MapElementSystem::Update(DeltaTime);
    MapElementListFilter<MapSystem::All> mapElementListFilter(mMapSystem->GetMapElementList(),SpawnSoldiersMapElement::GetType_static());
    for( MapElementListFilter<MapSystem::All>::const_iterator spawnSoldiersMapElementIt = mapElementListFilter.begin(), spawnSoldiersMapElementE = mapElementListFilter.end(); spawnSoldiersMapElementIt != spawnSoldiersMapElementE; ++spawnSoldiersMapElementIt )
    {
        Opt<SpawnSoldiersMapElement> spawnSoldiersMapElement(*spawnSoldiersMapElementIt);
        if (spawnSoldiersMapElement->GetValueId(SpawnSoldiersMapElement::SpawnNodeId)>0)
        {
            if (mProgramState.mMode==core::ProgramState::Server)
            {
                Opt<engine::SoldierSpawnSystem> soldierSpawnS(engine::SoldierSpawnSystem::Get());
                for (core::ProgramState::ClientDatas_t::iterator i=mProgramState.mClientDatas.begin(), e=mProgramState.mClientDatas.end();i!=e;++i)
                {
                    std::auto_ptr<Actor> player(soldierSpawnS->Spawn(*i));

                    mScene.AddActor(player.release());
                }
            }
            else if (mProgramState.mMode==core::ProgramState::Local)
            {
                Opt<core::ClientData> clientData(mProgramState.FindClientDataByClientId(mProgramState.mClientId));
                std::auto_ptr<Actor> Pl(engine::SoldierSpawnSystem::Get()->Spawn(*clientData));     

                Pl->Get<PlayerControllerComponent>()->SetEnabled(true);
                Pl->Get<PlayerControllerComponent>()->mActive=true;
                mScene.SetPlayerModels(Opt<Actor>(Pl.get()));
                mProgramState.mControlledActorGUID=clientData->mClientActorGUID;
                mScene.AddActor( Pl.release() );
            }
            L1("spawn soldiers!");
        }
        spawnSoldiersMapElement->ResetValues();
    }
}


} // namespace map

