#include "lt_top.h"
#include "lt_target.h"
#include "lt_transform.h"
#if 1 
Lt_top::Lt_top(sc_core::sc_module_name module_name)
:sc_module    
(module_name
)
,mem_target
("mem_target"
)
,arm_initiator
("arm_initiator"
)
{
	arm_initiator.trans_ptr->initiator_socket.bind(mem_target.memop_socket);
};
#endif
//Lt_top::Lt_top(){};