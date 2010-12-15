#ifndef API_IDENTITY_HH
#define API_IDENTITY_HH

#include "kvmxx.hh"
#include "memmap.hh"
#include <tr1/functional>
#include <tr1/memory>
#include <vector>

namespace identity {

struct hole {
    hole();
    hole(void* address, size_t size);
    void* address;
    size_t size;
};

class vm {
public:
    vm(kvm::vm& vm, mem_map& mmap, hole address_space_hole = hole());
private:
    typedef std::tr1::shared_ptr<mem_slot> mem_slot_ptr;
    std::vector<mem_slot_ptr> _slots;
};

class vcpu {
public:
    vcpu(kvm::vcpu& vcpu, std::tr1::function<void ()> guest_func,
	 unsigned long stack_size = 256 * 1024);
private:
    static void thunk(vcpu* vcpu);
    void setup_regs();
    void setup_sregs();
private:
    kvm::vcpu& _vcpu;
    std::tr1::function<void ()> _guest_func;
    std::vector<char> _stack;
};

}

#endif
