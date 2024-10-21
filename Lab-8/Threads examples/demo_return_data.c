#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// struct used for passing arguments to thread
struct thread_args {
	int num;
};

// struct used for retrieving date from thread
struct thread_ret {
	int len;
	int *arr;
};

void *fib(void *args) {
	struct thread_args *data = args;

	struct thread_ret *ret = (struct thread_ret *)malloc(sizeof(struct thread_ret));

	ret->arr = (int *)malloc(data->num*sizeof(int));
	ret->len = data->num;

	int a = 0;
	int b = 0;
	int c = 1;
	for (int i = 0; i < data->num; i++) {
		ret->arr[i] = c;
		a = b;
		b = c;
		c = a+b;
	}

	free(data);
	pthread_exit((void *)ret);
}

int main() {
	struct thread_args *data = (struct thread_args *)malloc(sizeof(struct thread_args));

	data->num = 10;

	pthread_t thread1;

	// using NULL in place of attr uses default value of attr (pthread_attr_init(attr))
	pthread_create(&thread1, NULL, fib, (void *)data);

	struct thread_ret *ret;

	// pthread_join expects to receive the address of the void* data returned by the thread
	// which means it expects void**
	pthread_join(thread1, (void **)&ret);

	for (int i = 0; i < ret->len; i++) {
		printf("%d\n", ret->arr[i]);
	}

	free(ret);
}
