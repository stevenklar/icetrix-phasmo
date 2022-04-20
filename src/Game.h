#pragma once
#include "pch.h"
#include "ImHotkey.h"

#define HOTKEY_PLAYERESP 0
#define HOTKEY_GHOSTESP 1
#define HOTKEY_OUIJABOARD 2
#define HOTKEY_BONE 3

extern std::vector<ImHotKey::HotKey> hotkeys;

namespace Phasmo
{
	struct MonitorData;
    struct GhostAI__Class;
    struct GhostInfo__Class;
    struct LevelRoom__Class;
    struct StateMachine;
    struct NavMeshAgent;
    struct GhostAudio;
    struct GhostInteraction;
    struct GhostActivity;
    struct SanityDrainer;
    struct Renderer__Array;
    struct LayerMask { int m_Mask; };
    struct __declspec(align(8)) Object_1__Fields { void* m_CachedPtr; };
    struct Component_1__Fields { struct Object_1__Fields _; };
    struct Behaviour__Fields { struct Component_1__Fields _; };
    struct MonoBehaviour__Fields { struct Behaviour__Fields _; };
    struct List_1_UnityEngine_BoxCollider_;
    struct Door__Array;
    struct List_1_UnityEngine_GameObject_;
	struct List_1_LightSwitch_;
    struct ParticleSystem;
    struct Player_1;
    struct Input;

    struct Quaternion {
        float x;
        float y;
        float z;
        float w;
    };

    struct __declspec(align(8)) String__Fields {
        int32_t m_stringLength;
        uint16_t m_firstChar;
    };

    struct String {
        struct String__Class* klass;
        struct MonitorData* monitor;
        struct String__Fields fields;
    };

    enum AnimatorUpdateMode {
        Normal = 0,
        AnimatePhysics = 1,
        UnscaledTime = 2,
    };

    enum HumanBodyBones {
        Hips = 0,
        LeftUpperLeg = 1,
        RightUpperLeg = 2,
        LeftLowerLeg = 3,
        RightLowerLeg = 4,
        LeftFoot = 5,
        RightFoot = 6,
        Spine = 7,
        Chest = 8,
        UpperChest = 54,
        Neck = 9,
        Head = 10,
        LeftShoulder = 11,
        RightShoulder = 12,
        LeftUpperArm = 13,
        RightUpperArm = 14,
        LeftLowerArm = 15,
        RightLowerArm = 16,
        LeftHand = 17,
        RightHand = 18,
        LeftToes = 19,
        RightToes = 20,
        LeftEye = 21,
        RightEye = 22,
        Jaw = 23,
        LeftThumbProximal = 24,
        LeftThumbIntermediate = 25,
        LeftThumbDistal = 26,
        LeftIndexProximal = 27,
        LeftIndexIntermediate = 28,
        LeftIndexDistal = 29,
        LeftMiddleProximal = 30,
        LeftMiddleIntermediate = 31,
        LeftMiddleDistal = 32,
        LeftRingProximal = 33,
        LeftRingIntermediate = 34,
        LeftRingDistal = 35,
        LeftLittleProximal = 36,
        LeftLittleIntermediate = 37,
        LeftLittleDistal = 38,
        RightThumbProximal = 39,
        RightThumbIntermediate = 40,
        RightThumbDistal = 41,
        RightIndexProximal = 42,
        RightIndexIntermediate = 43,
        RightIndexDistal = 44,
        RightMiddleProximal = 45,
        RightMiddleIntermediate = 46,
        RightMiddleDistal = 47,
        RightRingProximal = 48,
        RightRingIntermediate = 49,
        RightRingDistal = 50,
        RightLittleProximal = 51,
        RightLittleIntermediate = 52,
        RightLittleDistal = 53,
        LastBone = 55,
    };

    struct Animator {
        bool isHuman;
        bool hasRootMotion;
        app::Vector3 deltaPosition;
        Quaternion* deltaRotation;
        bool applyRootMotion;
        AnimatorUpdateMode updateMode;
        app::Vector3 pivotPosition;
        float speed;
        bool hasBoundPlayables;
        bool logWarnings;
    };

    enum LevelRoom___Enum {
        LevelRoom___Enum_basement = 0x00000000,
        LevelRoom___Enum_firstFloor = 0x00000001,
        LevelRoom___Enum_secondFloor = 0x00000002,
    };

    struct LevelRoom__Fields {
        struct MonoBehaviour__Fields _;
        struct List_1_UnityEngine_GameObject_* playersInRoom;
        struct List_1_LightSwitch_* lightSwitches;
        struct Door__Array* doors;
        struct List_1_UnityEngine_BoxCollider_* colliders;
        bool isOutsideRoom;
        struct BoxCollider* boxCollider;
        enum LevelRoom_Type__Enum floorType;
        struct String* roomName;
        float temperature;
        float startingTemperature;
        float currentPlayerInRoomTimer;
        bool isBasementOrAttic;
    };

    struct LevelRoom {
        struct LevelRoom__Class* klass;
        struct MonitorData* monitor;
        struct LevelRoom__Fields fields;
    };

    enum GhostTraits_Type__Enum {
        Spirit = 0,        // EMF 5, Box, Book
        Wraith = 1,        // EMF 5, Box, D.O.T.S.
        Phantom = 2,       // Box, Fingerprints, D.O.T.S.
        Poltergeist = 3,   // Box, Fingerprints, Book
        Banshee = 4,       // Fingerprints, Orb, D.O.T.S.
        Jinn = 5,          // EMF 5, Fingerprints, Freezing Temp
        Mare = 6,          // Box, Orb, Book
        Revenant = 7,      // Orb, Book, Freezing Temp
        Shade = 8,         // EMF 5, Book, Freezing Temp
        Demon = 9,         // Fingerprints, Book, Freezing Temp
        Yurei = 10,        // Orb, Freezing Temp, D.O.T.S.
        Oni = 11,          // EMF 5, Freezing Temp, D.O.T.S.
        Yokai = 12,        // Box, Orb, D.O.T.S
        Hantu = 13,        // Fingerprints, Orb, Freezing Temp
        Goryo = 14,        // EMF 5, Fingerprints, D.O.T.S.
        Myling = 15,       // EMF 5, Fingerprints, Book
        Onryo = 16,
		TheTwins = 17,
		Raiju = 18,
		Obake = 19,
    };

    enum GhostTraits_Evidence__Enum {
        None = 0,
		EMF = 1,
		SpiritBox = 2,
		Fingerprints = 3,
		GhostOrb = 4,
		GhostWritingBook = 5,
		Temperature = 6,
		DotsProjector = 7,
    };

    struct GhostTraits {
        enum GhostTraits_Type__Enum ghostType;
	    GhostTraits_Evidence__Enum* evidence;
        int ghostAge;
        bool isMale;
        struct String* GhostName;
        int ghostFirstNameID;
        int ghostLastNameID;
        bool isShy;
        int deathLength;
        int favouriteRoomID;
        bool someBool;
    };

    struct GhostInfo__Fields {
        struct MonoBehaviour__Fields _;
        struct PhotonView* view;
        struct GhostTraits ghostTraits;
        struct GhostAI* ghost;
        struct LevelRoom* favouriteRoom;
        float activityMultiplier;
    };

    struct GhostInfo {
        struct GhostInfo__Class* klass;
        struct MonitorData* monitor;
        struct GhostInfo__Fields fields;
    };

    enum GhostAI_States__Enum {
        idle = 0,
        wander = 1,
        hunting = 2,
        favouriteRoom = 3,
        light = 4,
        door = 5,
        throwing = 6,
        fusebox = 7,
        appear = 8,
        doorKnock = 9,
        windowKnock = 10,
        carAlarm = 11,
        radio = 12,
        flicker = 13,
        //lockDoor = 0x0000000e,
        cctv = 14,
        randomEvent = 15,
        GhostAbility = 16,
        //killPlayer = 0x00000012,
        //sink = 0x00000013,
        //sound = 0x00000014,
        //painting = 0x00000015,
        mannequin = 17,
        teleportObject = 18,
        //animationObject = 0x00000018,
        interact = 19,
    };

    struct GhostAI__Fields {
        struct MonoBehaviour__Fields _;
        struct StateMachine* stateMachine;
        enum GhostAI_States__Enum state;
        struct PhotonView* view;
        struct Animator* anim;
        struct GhostInfo* ghostInfo;
        struct NavMeshAgent* agent;
        struct GhostAudio* ghostAudio;
        struct GhostInteraction* ghostInteraction;
        struct GhostActivity* ghostActivity;
        struct SanityDrainer* sanityDrainer;
        struct Renderer__Array* myRends;
        bool ghostIsAppeared;
        struct Material* material;
        struct LayerMask mask;
        struct Transform* raycastPoint;
        struct Transform* raycastPoint2;
        //bool isChasingPlayer;
        float defaultSpeed;
        bool canEnterHuntingMode;
        bool someBool;
        float appearTimer;
        struct app::Vector3 someVector;
        struct GameObject* huntingPostProcessingVolume;
        bool isHunting;
        bool canAttack;
        bool smudgeSticksUsed;
        bool canWander;
        bool someBool2;
        struct Player_1* bansheeTarget;
        struct ParticleSystem* ghostParticle;
        struct Player_1* playerToKill;
    };

    struct GhostAI {
        struct GhostAI__Class* klass;
        struct MonitorData* monitor;
        struct GhostAI__Fields fields;
    };

    struct ClosetZone;

    struct Player_1__Fields {
        struct MonoBehaviour__Fields _;
        struct PhotonView* view;
        //bool beingHunted;
        bool isDead;
        int32_t modelID;
        //bool sanityChallengeHasBeenSet;
        struct ClosetZone *closetZone;
        struct PostProcessVolume* postProcessingVolume;
        struct PostProcessLayer* postProcessingLayer;
        struct PostProcessProfile* mainProfile;
        struct PostProcessProfile* deadProfile;
        struct GameObject* headObject;
        struct Breath* breath;
        struct List_1_Key_KeyType_* keys;
        struct Camera* cam;
        struct LevelRoom* currentRoom;
        struct Transform* mapIcon;
        struct PhotonObjectInteract* currentHeldObject;
        struct GameObject__Array* characterModels;
        struct GameObject* ghostDeathHands;
        struct LayerMask ghostRaycastMask;
        struct LayerMask mainLayerMask;
        struct PlayerHeadCamera* playerHeadCamera;
        struct Transform* aiTargetPoint;
        struct LayerMask noLayersMask;
        struct GameObject* deadBodyPrefab; // new
        struct AudioMixerSnapshot* interiorSnapshot;
        struct AudioMixerSnapshot* deathSnapshot;
        struct AudioMixerSnapshot* truckSnapshot;
        struct AudioMixerSnapshot* currentPlayerSnapshot;
        struct VoiceVolume* voiceVolume;
        struct Recorder* myVoiceRecorder;
        struct Speaker* myVoiceSpeaker; // new
        struct FootstepController* footstepController;
        struct AudioSource* keysAudioSource;  //struct AudioSource *evidenceAudioSource;
        struct AudioSource* deathAudioSource;
        struct AudioSource* chokingAudioSource;
        struct AudioSource* heartBeatAudioSource;
        struct AudioSource* sanityPillsAudioSource;
        struct VoiceOcclusion* voiceOcclusion;
        struct AudioMixer* masterAudio;
        float insanity;
        float sanityUpdateTimer;
        float sanityCheckTimer;
        struct RenderTexture* shadowRenderTexture;
        bool playerIsInLight;
        float difficultyRate;
        float normalSanityRate;
        float setupSanityRate;
        struct CharacterController* charController;
        struct AudioListener* listener;
        struct FirstPersonController* firstPersonController;
        struct PCPropGrab* pcPropGrab;
        struct DragRigidbodyUse* dragRigidBodyUse;
        struct PCCanvas* pcCanvas;
        struct PCCrouch* pcCrouch;
        struct PCPushToTalk* pcPushToTalk;
        struct PCMenu* pcMenu;
        struct PCControls* pcControls;
        struct PCFlashlight* pcFlashlight;
        struct Animator* charAnim;
        struct PlayerInput* playerInput;
        struct PCItemSway* itemSway;
        struct HxVolumetricCamera* hxVolumetricCamera;
        struct HxVolumetricImageEffect* hxVolumetricImageEffect;
        struct VRTK_InteractUse* leftHandInteractUse;
        struct VRTK_InteractUse* rightHandInteractUse;
        struct VRTK_InteractGrab* leftHandInteractGrab;
        struct VRTK_InteractGrab* rightHandInteractGrab;
        struct Transform* steamVRObj;
        struct VRMovementSettings* movementSettings;
        struct VRBelt* vrBelt;
        struct VRTK_SnapDropZone* leftVRBeltDropZone;
        struct VRTK_SnapDropZone* rightVRBeltDropZone; //struct GameObject *smoothVRCamera;
        struct VRTK_BodyPhysics* vrBodyPhysics;
        struct Transform* VRIKObj;
        struct VRTK_BasicTeleport* basicTeleport;
        struct VRTK_HeadsetCollision* headsetCollision;
        struct LIV* liv;
        struct TrailerCamera* trailerCamera;
        bool hasRun;
    };

    struct Player_1 {
        struct Player_1__Class* klass;
        struct MonitorData* monitor;
        struct Player_1__Fields fields;
    };

    enum Mission_MissionType__Enum {
        Mission_MissionType__Enum_none = 0x00000000,
        Mission_MissionType__Enum_main = 0x00000001,
        Mission_MissionType__Enum_side = 0x00000002,
    };

    struct Mission__Fields {
        struct MonoBehaviour__Fields _;
        struct PhotonView* view;
        enum Mission_MissionType__Enum type;
        bool completed;
        struct String* missionName;
        struct Text* myText;
        int32_t sideMissionID;
    };

    struct Mission {
        struct Mission__Class* klass;
        struct MonitorData* monitor;
        struct Mission__Fields fields;
    };

    struct Mission__VTable {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
    };

    struct Mission__Class {
        Il2CppClass_0 _0;
        Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
        struct Mission__StaticFields* static_fields;
        const Il2CppRGCTXData* rgctx_data;
        Il2CppClass_1 _1;
        struct Mission__VTable vtable;
    };

    struct MissionManager__Fields {
        struct MonoBehaviour__Fields _;
        struct List_1_System_Type_* mainMissions;
        struct List_1_System_Type_* sideMissions;
        struct Text* mainMissionText;
        struct Text* sideMissionText;
        struct Text* side2MissionText;
        struct Text* hiddenMissionText;
        struct Text* missionDescription;
        struct List_1_Mission_* currentMissions;
        struct PhotonView* view;
        bool hasCreatedMissions;
        int32_t missionIndex;
        bool hasSet;
        bool hasSetupMissions;
    };

    struct MissionManager {
        struct MissionManager__Class* klass;
        struct MonitorData* monitor;
        struct MissionManager__Fields fields;
    };

    struct Mission__Array {
        struct Mission__Array__Class* klass;
        struct MonitorData* monitor;
        struct Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct Mission* vector[32];
    };

    struct __declspec(align(8)) List_1_Mission___Fields {
        struct Mission__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_Mission_ {
        struct List_1_Mission___Class* klass;
        struct MonitorData* monitor;
        struct List_1_Mission___Fields fields;
    };

    enum RpcTarget__Enum {
        RpcTarget__Enum_All = 0x00000000,
        RpcTarget__Enum_Others = 0x00000001,
        RpcTarget__Enum_MasterClient = 0x00000002,
        RpcTarget__Enum_AllBuffered = 0x00000003,
        RpcTarget__Enum_OthersBuffered = 0x00000004,
        RpcTarget__Enum_AllViaServer = 0x00000005,
        RpcTarget__Enum_AllBufferedViaServer = 0x00000006,
    };

    struct ViveportAuth;
    struct EULAController;
    struct MainManager__Fields {
        struct MonoBehaviour__Fields _;
        struct Camera* sceneCamera;
        struct List_1_UnityEngine_Transform_* spawns;
        struct GameObject* vrPlayerModel;
        struct GameObject* pcPlayerModel;
        bool ranOnce;
        struct GameObject* serverObject;
        struct VRTK_UICanvas* vrtkCanvas;
        struct PCManager* pcManager;
        struct MyAudioManager* audioManager;
        struct StoreSDKManager* storeSDKManager;
        struct ControlsManager* controlsManager;
        struct ServerManager* serverManager;
        struct GameObject* RewardScreen;
        struct GameObject* FailureScreen;
        struct GameObject* TrainingScreen;
        struct GameObject* serverScreen;
        struct GameObject* ErrorScreen;
        struct GameObject* PhotoWarningScreen;
        struct Text* trainingGhostTypeText;
        struct Button* serverLobbyButton;
        struct Text* serverLobbyText;
        struct Text* serverVersionText;
        struct Player_1* localPlayer;
        int32_t connectionAttempts;
        struct SteamAuth* steamAuth;
        struct ViveportAuth *viveportAuth;
        struct EULAController *eulaController;
    };

    struct MainManager__Class;
    struct MainManager {
        struct MainManager__Class* klass;
        struct MonitorData* monitor;
        struct MainManager__Fields fields;
    };

/*
    struct PhotonView__Fields {
        struct MonoBehaviour__Fields _;
        int32_t ownerActorNr;
        uint8_t Group;
        bool mixedModeIsReliable;
        int32_t prefixField;
        enum PhotonView_ObservableSearch__Enum observableSearch;
        struct Object__Array* instantiationDataField;
        struct List_1_System_Object_* lastOnSerializeDataSent;
        struct List_1_System_Object_* syncValues;
        struct Object__Array* lastOnSerializeDataReceived;
        enum ViewSynchronization__Enum Synchronization;
        enum OwnershipOption__Enum OwnershipTransfer;
        struct List_1_UnityEngine_Component_* ObservedComponents;
        struct Queue_1_Photon_Pun_PhotonView_CallbackTargetChange_* CallbackChangeQueue;
        struct List_1_Photon_Pun_IOnPhotonViewPreNetDestroy_* OnPreNetDestroyCallbacks;
        struct List_1_Photon_Pun_IOnPhotonViewOwnerChange_* OnOwnerChangeCallbacks;
        struct List_1_Photon_Pun_IOnPhotonViewControllerChange_* OnControllerChangeCallbacks;
        int32_t viewIdField;
        int32_t InstantiationId;
        struct Player* owner;
        struct Player* controller;
        int32_t controllerActorNr;
        enum PhotonView_OwnershipCacheState__Enum ownershipCacheIsValid;
        bool amController;
        bool _AmOwner_k__BackingField;
        bool didAwake;
        bool isRuntimeInstantiated;
        bool removedFromLocalViewList;
        struct MonoBehaviour__Array* RpcMonoBehaviours;
    };
*/
    struct PhotonView__Fields {
        struct MonoBehaviour__Fields _;
        uint8_t Group;
        int32_t prefixField;
        struct Object__Array *instantiationDataField;
        struct List_1_System_Object_ *lastOnSerializeDataSent;
        struct List_1_System_Object_ *syncValues;
        struct Object__Array *lastOnSerializeDataReceived;
        enum ViewSynchronization__Enum Synchronization;
        bool mixedModeIsReliable;
        enum OwnershipOption__Enum OwnershipTransfer;
        enum PhotonView_ObservableSearch__Enum observableSearch;
        struct List_1_UnityEngine_Component_ *ObservedComponents;
        struct MonoBehaviour__Array *RpcMonoBehaviours;
        bool _IsMine_k__BackingField;
        struct Player *_Controller_k__BackingField;
        int32_t _CreatorActorNr_k__BackingField;
        bool _AmOwner_k__BackingField;
        struct Player *_Owner_k__BackingField;
        int32_t ownerActorNr;
        int32_t controllerActorNr;
        int32_t sceneViewId;
        int32_t viewIdField;
        int32_t InstantiationId;
        bool isRuntimeInstantiated;
        bool removedFromLocalViewList;
        struct Queue_1_Photon_Pun_PhotonView_CallbackTargetChange_ *CallbackChangeQueue;
        struct List_1_Photon_Pun_IOnPhotonViewPreNetDestroy_ *OnPreNetDestroyCallbacks;
        struct List_1_Photon_Pun_IOnPhotonViewOwnerChange_ *OnOwnerChangeCallbacks;
        struct List_1_Photon_Pun_IOnPhotonViewControllerChange_ *OnControllerChangeCallbacks;
    };

    struct PhotonView {
        struct PhotonView__Class* klass;
        struct MonitorData* monitor;
        struct PhotonView__Fields fields;
    };

    struct __declspec(align(8)) Player__Fields {
        struct Room* _RoomReference_k__BackingField;
        int32_t actorNumber;
        bool IsLocal;
        bool _HasRejoined_k__BackingField;
        struct String* nickName;
        struct String* _UserId_k__BackingField;
        bool _IsInactive_k__BackingField;
        struct Hashtable_1* _CustomProperties_k__BackingField;
        struct Object* TagObject;
    };

    struct Player {
        struct Player__Class* klass;
        struct MonitorData* monitor;
        struct Player__Fields fields;
    };

    struct JournalController__Fields {
        struct MonoBehaviour__Fields _;
        struct PauseMenuController* pauseMenuController;
        struct PauseAudioManager* pauseAudioManager;
        struct GameObject* content;
        struct GameObject* pauseMenu;
        struct GameObject* journalMenu;
        struct GamePCManager* pcManager;
        struct GameVRManager* vrManager;
        struct GameGraphicsManager* graphicManager;
        struct Canvas* canvas;
        struct AudioSource* openSource;
        struct AudioClip* openClip;
        struct AudioClip* closeClip;
        struct AudioClip* pauseFlip;
        struct AudioClip__Array* pageTurns;
        bool isOpen;
        bool isVRJournal;
        struct GameObject__Array* pages;
        struct GameObject* left;
        struct GameObject* right;
        int32_t index;
        struct PhotonView* view;
    };

    /*
    struct JournalController__Fields {
        struct MonoBehaviour__Fields _;
        struct GameObject* content;
        struct Canvas* canvas;
        struct AudioSource* openSource;
        struct AudioClip* openClip;
        struct AudioClip* closeClip;
        bool isOpen;
        bool isVRJournal;
        struct GameObject__Array* pages;
        int32_t index;
        struct Image__Array* photos;
        struct Text__Array* photosNames;
        int32_t photosAmount;
        int32_t resWidth;
        int32_t resHeight;
        struct PhotonView* view;
        int32_t keyAmount;
        struct Text* Key1Text;
        struct Text* Key2Text;
        struct Text* Key3Text;
        struct Text* Key4Text;
        struct Text* Key5Text;
        struct Text* Key6Text;
        struct List_1_JournalController_Ghost_* values;
        struct List_1_JournalController_Ghost_* ghosts;
        struct List_1_System_String_* evidenceNames;
        struct Text* evidence1Text;
        int32_t evidence1Index;
        struct Text* evidence2Text;
        int32_t evidence2Index;
        struct Text* evidence3Text;
        int32_t evidence3Index;
        struct Text* ghostTypeText;
        int32_t ghostTypeIndex;
    };
    */

    struct JournalController {
        struct JournalController__Class* klass;
        struct MonitorData* monitor;
        struct JournalController__Fields fields;
    };

    enum CollisionFlags__Enum {
        CollisionFlags__Enum_None = 0x00000000,
        CollisionFlags__Enum_Sides = 0x00000001,
        CollisionFlags__Enum_Above = 0x00000002,
        CollisionFlags__Enum_Below = 0x00000004,
        CollisionFlags__Enum_CollidedSides = 0x00000001,
        CollisionFlags__Enum_CollidedAbove = 0x00000002,
        CollisionFlags__Enum_CollidedBelow = 0x00000004,
    };

    struct GameController__Fields {
        struct MonoBehaviour__Fields _;
        struct PlayerData* myPlayer;
        struct UnityEvent* OnAllPlayersConnected;
        struct UnityEvent* OnPlayerSpawned;
        struct UnityEvent* OnLocalPlayerSpawned;
        struct UnityEvent* OnPlayerDisconnected;
        struct UnityEvent* OnGhostSpawned;
        struct UnityEvent* OnSomething1;
        struct UnityEvent* OnSomething2;
        struct List_1_PlayerData_* playersData;
        float currentAverageSanity;
        struct SteamVR_LoadLevel* loadLevel;
        struct PhotonView* view;
        struct SpeechRecognitionController* speechRecognitionController; // 0x78
        struct LevelController* levelController; // 0x80
        struct MultiplayerController* multiplayerController; // 0x88
        bool allPlayersAreConnected;
        bool isLoadingBackToMenu;
        struct GameObject* pcLoadingCanvas; // 0x98
        enum Contract_LevelDifficulty__Enum levelDifficulty;
        struct Material* material; // 0xA8
    };

    struct GameController {
        struct GameController__Class* klass;
        struct MonitorData* monitor;
        struct GameController__Fields fields;
    };

    struct __declspec(align(8)) PlayerData__Fields {
        struct Player_1* player;
        struct Player* photonPlayer;
        struct String* playerName;
    };

    struct PlayerData {
        struct PlayerData__Class* klass;
        struct MonitorData* monitor;
        struct PlayerData__Fields fields;
    };

    struct __declspec(align(8)) List_1_PlayerData___Fields {
        struct PlayerData__Array* _items;
        int32_t _size;
        int32_t _version;
        struct Object* _syncRoot;
    };

    struct List_1_PlayerData_ {
        struct List_1_PlayerData___Class* klass;
        struct MonitorData* monitor;
        struct List_1_PlayerData___Fields fields;
    };

    struct PlayerData__Array {
        struct PlayerData__Array__Class* klass;
        struct MonitorData* monitor;
        struct Il2CppArrayBounds* bounds;
        il2cpp_array_size_t max_length;
        struct PlayerData* vector[32];
    };

    struct IEnumerator_1_PlayerData_ {
        struct IEnumerator_1_PlayerData___Class* klass;
        struct MonitorData* monitor;
    };
}
