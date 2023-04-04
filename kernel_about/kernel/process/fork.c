u16 get_newpid()
{
	u16 i = 0;
	struct ** p = &task_struct[0];
	while(++i<MAX_TASK)
	{
		if(*++p)continue;
		return i;
	}
	return MAX_TASK;
}
