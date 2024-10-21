#include <pthread.h> // use '-lpthread' flag while compiling to link the library
#include <stdlib.h>
#include <stdio.h>

// struct used for passing arguments to thread
struct thread_data {
	char *name;
	char *id;
	int age;
};

void *printer(void *args) {
	struct thread_data *data = args; // typecaste void pointer to thread_data struct

	printf("%s\n", data->name);
	printf("%s\n", data->id);
	printf("%d\n", data->age);

	free(data);
	pthread_exit(NULL);
}

int main() {
	struct thread_data *data = (struct thread_data *)malloc(sizeof(struct thread_data));

	data->name = "Smitesh";
	data->id = "2018A7PS0167G";
	data->age = 21;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_t thread1; // variable to hold thread identifier

	// create threads
	// arg1 : thread1 will be filled with thread identifier
	// arg2 : attr will be used to determine attributes
	// arg3 : function pointer "(void *)(* myfunc)(void *)" to the function that will run in new thread
	// arg4 : void pointer that will be passed to function (in arg3) as the argument
	pthread_create(&thread1, &attr, printer, (void *)data);

	pthread_join(thread1, NULL);
}
