#ifndef STATETEMPLATE_H
#define STATETEMPLATE_H

#include <map>

#define DynamicStateCreate(classname, enumtype) \
    static void* CreateState() { return new classname; } \
    RobotStateType GetState() const { return enumtype; }

#define DynamicStateBind(classname) \
    reinterpret_cast<CreateInstancePtr>( &(classname::CreateState) )

template <typename EnumType, typename T>
class StateTemplate
{
public:
    StateTemplate() {}
    virtual ~StateTemplate() {}

    void SetParentObj(T *obj)
    {
        pParentObj_ = obj;
    }

    virtual EnumType GetState() const = 0;
    virtual EnumType Update() = 0;

    virtual void EnterState() = 0;
    virtual void LeaveState() = 0;

protected:
    T *pParentObj_;
};

template <typename EnumType, typename StateClass, class T>
class StateTemplateMgr
{
public:
    typedef StateClass *(*CreateInstancePtr)();

    StateTemplateMgr() : pState_(nullptr) {}
    virtual ~StateTemplateMgr()
    {
        if (pState_ != nullptr)
            delete pState_;
    }

    void InitStateTemplateMgr(EnumType defaultState)
    {
        defaultState_ = defaultState;
        RegisterState();
    }

    void RegisterStateClass(EnumType state, CreateInstancePtr ptr)
    {
        dynamicCreateMap_[state] = ptr;
    }

    StateClass *CreateStateObj(EnumType state)
    {
        auto it = dynamicCreateMap_.find(state);
        if (it == dynamicCreateMap_.end())
            return nullptr;

        CreateInstancePtr np = it->second;
        StateClass *pState = np();
        pState->SetParentObj(static_cast<T *>(this));
        return pState;
    }

    void ChangeState(EnumType state);
    void UpdateState();

protected:
    virtual void RegisterState() = 0;

protected:
    std::map<EnumType, CreateInstancePtr> dynamicCreateMap_;

    EnumType defaultState_;
    StateClass *pState_;
};

template <typename EnumType, typename StateClass, typename T>
void StateTemplateMgr<EnumType, StateClass, T>::ChangeState(EnumType state)
{
    StateClass *pNewState = CreateStateObj(state);
    if (pNewState == nullptr)
        return;

    if (pState_ != nullptr)
    {
        pState_->LeaveState();
        delete pState_;
    }

    pState_ = pNewState;
    pState_->EnterState();
}

template <typename EnumType, typename StateClass, typename T>
void StateTemplateMgr<EnumType, StateClass, T>::UpdateState()
{
    if (pState_ == nullptr)
        ChangeState(defaultState_);

    EnumType curState = pState_->Update();
    if (curState != pState_->GetState())
    {
        ChangeState(curState);
    }
}

#endif