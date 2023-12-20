#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <getopt.h>

// Мьютекс для обеспечения безопасности доступа к глобальным данным
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long long main_result = 1; // Результат факториала

// Структура для передачи параметров в поток
struct ThreadData {
    int start; // начало (с какого числа поток будет считать)
    int end; // конец (до какого числа поток будет считать)
    int thread_id; // Идентификатор потока
};

void partial_factorial(void *args) {
  struct ThreadData *thr_data = (struct ThreadData *)args;
  int start = thr_data->start;
  int end = thr_data->end;
  int thread_id = thr_data->thread_id;

  long long current_result = 1;

  // Вычисление части факториала для данного потока
  for (int i = start; i <= end; i++) {
    current_result = (current_result * i);
  }

  // Захватываем мьютекс для обновления глобального результата
  pthread_mutex_lock(&mutex);
  main_result = (main_result * current_result);
  pthread_mutex_unlock(&mutex);

  printf("thread %d calculated  -  %lld\n", thread_id, current_result);

  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  int k = -1; // number for factorial
  int pnum = -1; // number of threads
  int mod = -1; // mode for factorial

  while (1) {
    int option_index = 0;
    static struct option long_options[] = {
      {"k", required_argument, 0, 'k'},
      {"pnum", required_argument, 0, 'p'},
      {"mod", required_argument, 0, 'm'},
      {0, 0, 0, 0}};

    int c = getopt_long(argc, argv, "k:p:m:", long_options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 'k':
        sscanf(optarg, "%d", &k);
        break;
      case 'p':
        sscanf(optarg, "%d", &pnum);
        break;
      case 'm':
        sscanf(optarg, "%d", &mod);
        break;
      default:
        fprintf(stderr, "Input format: %s -k <number> --pnum=<threads> --mod=<modulus>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  // Checking for required params
  if (k == -1 || pnum == -1 || mod == -1) {
    fprintf(stderr, "Input format: %s -k <number> --pnum=<threads> --mod=<modulus>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Array of thread's id
  pthread_t threads[pnum];
  // Array of data for threads
  struct ThreadData thread_data[pnum];


  int start_counter = 1;
  int end_counter = 1;

  int pnum_counter = pnum; // 4
  int k_counter = k; // 10

  for (int i = 0; i < pnum; i++) {
    end_counter = start_counter + k_counter / pnum_counter - 1;

    pnum_counter -= 1;
    k_counter -= (end_counter - start_counter + 1);

    thread_data[i].start = start_counter;
    thread_data[i].end = end_counter;
    thread_data[i].thread_id = i + 1;

    if (pthread_create(&threads[i], NULL, (void *(*)(void *))partial_factorial, (void *)&thread_data[i]) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    start_counter = end_counter + 1;
  }

  // Stoping all threads
  for (int i = 0; i < pnum; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }

  // Using mutex
//   pthread_mutex_lock(&mutex);
  long long final_result = main_result % mod;
//   pthread_mutex_unlock(&mutex);
  printf("factorial %d = %d \n", k, main_result);

  printf("%d mod %d = %lld\n", main_result, mod, final_result);


  pthread_mutex_destroy(&mutex);

  return 0;
}