// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Target Unity version: 2019.4.0 - 2019.4.99

// ******************************************************************************
// * IL2CPP application-specific method definition addresses and signatures
// ******************************************************************************
using namespace app;

// ____________________________________________________________________________
// Auto
// UnityEngine
DO_FUNC(int32_t, Screen_get_height, (MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Screen::get_height()");
DO_FUNC(Resolution, Screen_get_currentResolution, (MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Resolution UnityEngine.Screen::get_currentResolution()");
DO_FUNC(float, Time_get_deltaTime, (MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Time::get_deltaTime()");
DO_FUNC(float, Time_get_timeScale, (MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Time::get_timeScale()");
DO_FUNC(void, Time_set_timeScale, (float value, MethodInfo * method), "UnityEngine.CoreModule, System.Void UnityEngine.Time::set_timeScale(System.Single)");
DO_FUNC(CursorLockMode__Enum, Cursor_get_lockState, (MethodInfo * method), "UnityEngine.CoreModule, UnityEngine.CursorLockMode UnityEngine.Cursor::get_lockState()");
DO_FUNC(void, Cursor_set_lockState, (CursorLockMode__Enum value, MethodInfo * method), "UnityEngine.CoreModule, System.Void UnityEngine.Cursor::set_lockState(UnityEngine.CursorLockMode)");
DO_FUNC(Transform*, Component_1_get_transform, (Component_1 * __this, MethodInfo * method), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.Component::get_transform()");
DO_FUNC(Component_1*, Component_GetComponent, (Component_1 * __this, Type type, MethodInfo * method), "UnityEngine.CoreModule, UnityEngine.Component UnityEngine.Component::GetComponent(System.Type)");
DO_FUNC(bool, Behaviour_get_isActiveAndEnabled, (Behaviour * __this, MethodInfo * method), "UnityEngine.CoreModule, System.Boolean UnityEngine.Behaviour::get_isActiveAndEnabled()");
DO_FUNC(Camera*, Camera_get_main, (MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Camera UnityEngine.Camera::get_main()");
DO_FUNC(Vector3, Camera_WorldToScreenPoint_1, (Camera * __this, Vector3 position, MethodInfo * method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Camera::WorldToScreenPoint(UnityEngine.Vector3)");
DO_FUNC(float, Camera_get_fieldOfView, (Camera* __this, MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Camera::get_fieldOfView()");
DO_FUNC(void, Camera_set_fieldOfView, (Camera* __this, float value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Camera::set_fieldOfView(System.Single)");

DO_FUNC(Transform*, Animator_GetBoneTransform, (Animator* __this, HumanBodyBones__Enum humanBoneId, MethodInfo* method), "UnityEngine.AnimationModule, UnityEngine.Transform UnityEngine.Animator::GetBoneTransform(UnityEngine.HumanBodyBones)");

DO_FUNC(void, SceneManager_LoadScene_1, (String* sceneName, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.SceneManagement.SceneManager::LoadScene(System.String)");
DO_FUNC(Vector3, LineRenderer_GetPosition, (LineRenderer* __this, int32_t index, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.LineRenderer::GetPosition(System.Int32)");
DO_FUNC(float, Input_GetAxis, (String* axisName, MethodInfo* method), "UnityEngine.InputLegacyModule, System.Single UnityEngine.Input::GetAxis(System.String)");

DO_FUNC(Vector3, Transform_get_position, (Transform * __this, MethodInfo * method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Transform::get_position()");
DO_FUNC(void, Transform_set_position, (Transform * __this, Vector3 value, MethodInfo * method), "UnityEngine.CoreModule, System.Void UnityEngine.Transform::set_position(UnityEngine.Vector3)");
DO_FUNC(Quaternion, Transform_get_localRotation, (Transform* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Quaternion UnityEngine.Transform::get_localRotation()");
DO_FUNC(void, Transform_set_localRotation, (Transform* __this, Quaternion value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Transform::set_localRotation(UnityEngine.Quaternion)");

DO_FUNC(Vector3, Transform_get_forward, (Transform * __this, MethodInfo * method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Transform::get_forward()");
DO_FUNC(Vector3, Transform_get_right, (Transform * __this, MethodInfo * method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Transform::get_right()");

DO_FUNC(Quaternion, Quaternion_AngleAxis, (float angle, Vector3 axis, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Quaternion UnityEngine.Quaternion::AngleAxis(System.Single, UnityEngine.Vector3)");
DO_FUNC(Quaternion, Quaternion_op_Multiply, (Quaternion lhs, Quaternion rhs, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Quaternion UnityEngine.Quaternion::op_Multiply(UnityEngine.Quaternion, UnityEngine.Quaternion)");

DO_FUNC(Vector3, Vector3_get_up, (MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Vector3::get_up()");
DO_FUNC(Vector3, Vector3_get_left, (MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Vector3::get_left()");

// Assembly-CSharp
DO_FUNC(void, GhostAI_Awake, (GhostAI* __this, MethodInfo* method), "Assembly-CSharp, System.Void GhostAI::Awake()");
DO_FUNC(void, GhostAI_Update, (GhostAI* __this, MethodInfo* method), "Assembly-CSharp, System.Void GhostAI::Update()");
DO_FUNC(void, GhostAI_Appear, (GhostAI * __this, bool isEvent, MethodInfo * method), "Assembly-CSharp, System.Void GhostAI::Appear(System.Boolean)");
DO_FUNC(void, GhostAI_UnAppear, (GhostAI * __this, bool isEvent, MethodInfo * method), "Assembly-CSharp, System.Void GhostAI::UnAppear(System.Boolean)");
DO_FUNC(void, FirstPersonController_FixedUpdate, (FirstPersonController* __this, MethodInfo* method), "Assembly-CSharp-firstpass, System.Void UnityStandardAssets.Characters.FirstPerson.FirstPersonController::FixedUpdate()");
// BROKEN
DO_FUNC(void, GhostAI_Hunting, (GhostAI* __this, bool isHunting, MethodInfo* method), "Assembly-CSharp, System.Void GhostAI::Hunting(System.Boolean)");
//DO_FUNC(void, GhostAI_ChasingPlayer, (GhostAI* __this, bool chasing, MethodInfo* method), "Assembly-CSharp, System.Void GhostAI::____________(System.Boolean)");
DO_FUNC(void, GhostAI_ChangeState, (GhostAI* __this, GhostAI___Enum state, PhotonObjectInteract* obj, PhotonObjectInteract__Array* objects, MethodInfo* method), "Assembly-CSharp, System.Void GhostAI::ChangeState(GhostAI.αñ₧αñóαñ₧αññαñ¥αñƒαññαñ¢αñªαñ₧αñƒ, PhotonObjectInteract, PhotonObjectInteract[])");
DO_FUNC(void, Player_1_Awake, (Player_1 * __this, MethodInfo* method), "Assembly-CSharp, System.Void Player::Awake()");
DO_FUNC(void, Player_1_Update, (Player_1* __this, MethodInfo* method), "Assembly-CSharp, System.Void Player::Update()");
DO_FUNC(void, GameController_Start, (GameController* __this, MethodInfo* method), "Assembly-CSharp, System.Void GameController::Start()");
DO_FUNC(void, GameController_Exit, (GameController* __this, MethodInfo* method), "Assembly-CSharp, System.Void GameController::Exit()");
DO_FUNC(IEnumerator*, MainManager_Start, (MainManager* __this, MethodInfo* method), "Assembly-CSharp, System.Collections.IEnumerator MainManager::Start()");
DO_FUNC(void, RewardManager_Awake, (RewardManager* __this, MethodInfo* method), "Assembly-CSharp, System.Void RewardManager::Awake()");
DO_FUNC(void, MissionManager_Awake, (MissionManager* __this, MethodInfo* method), "Assembly-CSharp, System.Void MissionManager::Awake()");
//DO_FUNC(void, OuijaBoard_Awake, (OuijaBoard* __this, MethodInfo* method), "Assembly-CSharp, System.Void OuijaBoard::Awake()");
DO_FUNC(void, OuijaBoard_Start, (OuijaBoard* __this, MethodInfo* method), "Assembly-CSharp, System.Void OuijaBoard::Start()");
DO_FUNC(void, DNAEvidence_Start, (DNAEvidence* __this, MethodInfo* method), "Assembly-CSharp, System.Void DNAEvidence::Start()");
DO_FUNC(void, JournalController_OnEnable, (JournalController* __this, MethodInfo* method), "Assembly-CSharp, System.Void JournalController::OnEnable()");
DO_FUNC(void, JournalController_OnDisable, (JournalController* __this, MethodInfo* method), "Assembly-CSharp, System.Void JournalController::OnDisable()");
DO_FUNC(void, Mission_Completed, (Mission* __this, MethodInfo* method), "Assembly-CSharp, System.Void Mission::Completed()");
DO_FUNC(void, PCStamina_Update, (PCStamina* __this, MethodInfo* method), "Assembly-CSharp, System.Void PCStamina::Update()");

// Sound test
DO_FUNC(void, HouseAmbientSoundController_PlaySound, (HouseAmbientSoundController* __this, Vector3 pos, int32_t clipID, MethodInfo* method), "Assembly-CSharp, System.Void HouseAmbientSoundController::PlaySound(UnityEngine.Vector3, System.Int32)");
DO_FUNC(void, AudioSource_Play, (AudioSource* __this, MethodInfo* method), "UnityEngine.AudioModule, System.Void UnityEngine.AudioSource::Play()");
DO_FUNC(void, AudioSource_PlayOneShot, (AudioSource* __this, AudioClip* clip, MethodInfo* method), "UnityEngine.AudioModule, System.Void UnityEngine.AudioSource::PlayOneShot(UnityEngine.AudioClip)");
DO_FUNC(void, AudioSource_PlayOneShot_1, (AudioSource* __this, AudioClip* clip, float volumeScale, MethodInfo* method), "UnityEngine.AudioModule, System.Void UnityEngine.AudioSource::PlayOneShot(UnityEngine.AudioClip, System.Single)");

// PhotonUnityNetworking
DO_FUNC(bool, PhotonNetwork_get_IsMasterClient, (MethodInfo * method), "PhotonUnityNetworking, System.Boolean Photon.Pun.PhotonNetwork::get_IsMasterClient()");
DO_FUNC(ServerSettings *, PhotonNetwork_get_PhotonServerSettings, (MethodInfo * method), "PhotonUnityNetworking, Photon.Pun.ServerSettings Photon.Pun.PhotonNetwork::get_PhotonServerSettings()");
DO_FUNC(bool, PhotonView_get_IsOwnerActive, (PhotonView * __this, MethodInfo * method), "PhotonUnityNetworking, System.Boolean Photon.Pun.PhotonView::get_IsOwnerActive()");
DO_FUNC(void, PhotonView_RPC, (PhotonView * __this, String * methodName, RpcTarget__Enum target, Object__Array * parameters, MethodInfo * method), "PhotonUnityNetworking, System.Void Photon.Pun.PhotonView::RPC(System.String, Photon.Pun.RpcTarget, System.Object[])");
DO_FUNC(bool, PhotonNetwork_SetMasterClient, (Player* masterClientPlayer, MethodInfo* method), "PhotonUnityNetworking, System.Boolean Photon.Pun.PhotonNetwork::SetMasterClient(Photon.Realtime.Player)");
DO_FUNC(Player*, PhotonNetwork_get_LocalPlayer, (MethodInfo* method), "PhotonUnityNetworking, Photon.Realtime.Player Photon.Pun.PhotonNetwork::get_LocalPlayer()");

// AntiCheat
DO_FUNC(bool, ADetector_get_CheatDetected, (ADetector* __this, MethodInfo* method), "AntiCheat, System.Boolean OPS.AntiCheat.Detector.ADetector::get_CheatDetected()");
DO_FUNC(void, ADetector_OnCheatDetected, (ADetector* __this, MethodInfo* method), "AntiCheat, System.Void OPS.AntiCheat.Detector.ADetector::OnCheatDetected()");

