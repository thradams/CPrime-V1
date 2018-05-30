
void Run(void(*callback)(void*), void* data);

static void _lambda_1(void* data)
		{
			printf("second\n");
		}

static void _lambda_0(void* data)
	{
		printf("first\n");
		Run(_lambda_1, 0);
	}


int main()
{
	Run(_lambda_0, 0);

}