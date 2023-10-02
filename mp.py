import multiprocessing

class mp_work:
    '''
        进程池完成特定的工作

        `num_processes` 进程池中进程的数量

        `work_func` 处理任务时使用的函数，函数应当具备一个参数，是待处理的数据
    '''
    def __init__(self, num_processes,work_func):
        self.num_processes = num_processes
        self.pool = multiprocessing.Pool(processes=num_processes)
        self.result_queue = multiprocessing.Manager().Queue(maxsize=1000)
        self.work_func = work_func
        self.r = []

    def process_data(self, data):
        '''
            向进程池中添加待处理的一组数据
        '''
        for d in data:
            self.r.append(self.pool.apply_async(self.work_func, args=(d,), callback=self.result_queue.put))

    def get_results(self):
        '''
            获得一个任务在处理完毕后的结果

            可以使用
            
            ```
                for result in mp.get_results():
                    print(result)
            ```

            进行迭代
        '''
        while not self.result_queue.empty():
            yield self.result_queue.get()

    def is_done(self):
        '''
            判断所有给定的任务是否都已经处理完毕，如果返回True,
            
            那么在你不再增加新任务的情况下，你就可以调用close函数销毁此对象
        '''
        if not all(r.ready() for r in self.r):
            return False
        if not self.result_queue.empty():
            return False
        return True

    def __del__(self):
        self.pool.close()
        self.pool.join()
