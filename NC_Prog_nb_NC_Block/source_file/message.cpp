#include "..\pch.h"
#include "message.h"

#define NC_Prog_nb_NC_Block_EXPORTS

block_message::block_message()
{
	ans_message = 0;
	error_message = 0;
}

block_message::block_message(block_message& a)
{
	ans_message = a.ans_message;
	error_message = a.error_message;
}
