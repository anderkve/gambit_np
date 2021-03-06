#ifndef __WRAPPERBASE__
#define __WRAPPERBASE__

__START_GAMBIT_NAMESPACE__

class AbstractBase;

class WrapperBase
{
    protected:
        AbstractBase* BEptr;
        bool delete_BEptr;
    public:
        bool can_delete_BEptr() { return delete_BEptr; }
        void set_delete_BEptr(bool del_wrp_in) { delete_BEptr = del_wrp_in; }

    public:
        WrapperBase(AbstractBase* BEptr_in) : BEptr(BEptr_in), delete_BEptr(true) {}

        virtual ~WrapperBase() {}
};

__END_GAMBIT_NAMESPACE__

#endif /* __WRAPPERBASE__ */
