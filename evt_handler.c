#include "main.h"

/**
 * evt_handler - handle event interuption
 * @signum: int val of the interuption
 */
void evt_handler(int __attribute__((unused)) signum)
{
	char *prompt = "\n ($)";

	write(1, prompt, 5);
}
