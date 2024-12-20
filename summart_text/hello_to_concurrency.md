### Concurrency

Concurrency is the simultaneous execution of multiple activities, either as a natural part of life or within computer systems. In computing, concurrency can be achieved via task switching on single-core processors or through genuine parallel execution on multicore or multiprocessor systems. 

In single-core systems, concurrency is an illusion created by rapid task switching. The operating system performs context switching, which involves saving and restoring CPU states and managing memory, to allow multiple tasks to appear as though they are running simultaneously. However, this introduces overhead and delays, especially with more tasks than available hardware threads.

With multicore or multiprocessor systems, true concurrency is possible, where tasks execute genuinely in parallel. The number of hardware threads determines the system's capacity for running tasks concurrently. Even in such systems, task switching is often required when the number of tasks exceeds the available hardware threads.

The design and implementation of concurrent applications depend heavily on the level of hardware concurrency available. Although the techniques discussed in the book are applicable across different hardware configurations, optimizing concurrency requires awareness of these hardware limitations and considerations.

---

### Important Points

1. **Definition of Concurrency**:
   - Concurrency refers to the simultaneous execution of multiple independent activities.
   - In life: Examples include walking and talking simultaneously.
   - In computing: A system performs multiple tasks either genuinely or through the illusion of concurrency.

2. **Concurrency in Single-Core Systems**:
   - Achieved through **task switching**.
   - The OS saves and restores CPU states and manages memory during **context switching**.
   - Concurrency is an illusion, as tasks execute sequentially but switch rapidly.

3. **Hardware Concurrency**:
   - Genuine parallelism occurs in systems with multiple cores or processors.
   - The measure of parallelism is the number of **hardware threads**.
   - Task switching is still needed when tasks exceed available hardware threads.

4. **Performance Implications**:
   - Context switching introduces delays due to overhead in saving/restoring states and memory operations.
   - Multicore systems reduce such delays by genuinely running tasks in parallel, avoiding interleaving.

5. **Application Design**:
   - Techniques for concurrency are applicable across all hardware configurations.
   - Optimization depends on understanding and leveraging the available hardware concurrency.

6. **Illustrative Scenarios**:
   - **Single-core systems**: Tasks interleave with delays caused by context switching.
   - **Dual-core systems**: Tasks run simultaneously on separate cores, achieving true concurrency.

7. **Relevance of Concurrency in Modern Systems**:
   - Multicore processors are increasingly common in desktops and other devices.
   - Even in systems with hardware concurrency, the OS handles hundreds of background tasks using task switching.

8. **Future Topics**:
   - Memory models (Chapter 5) and designing efficient concurrent code (Chapter 8) are crucial for understanding and optimizing concurrency.
