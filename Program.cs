using System.Diagnostics;

namespace CsharpCountPrimes
{
    internal class Program
    {
        static int NumberOfThreads = Environment.ProcessorCount;
        static int NumberOfThreadsThreshold = 9;
        static void Main(string[] args)
        {
            int argsCount = args.Count();
            long number = 1000000;
            if (argsCount > 2)
            {
                Console.WriteLine("Error: More than 2 arguments passed");
                return;
            }
            if (argsCount > 0 && (args[0] == "-h" || args[0] == "--help"))
            {
                Console.WriteLine("How to use:\n\tcsharp_count_primes *Number*\n\tcsharp_count_primes *Threads* *Number*");
                return;
            }
            if (argsCount == 1)
            {
                long tempNumber = 0;
                if (!long.TryParse(args[0], out tempNumber))
                {
                    Console.WriteLine("Argument must be a number");
                    return;
                }
                if(tempNumber < 2){
                    Console.WriteLine("Number must bigger than 1");
                    return;
                }
                number = tempNumber;
            }
            if (argsCount == 2)
            {
                int tempThreads = 0;
                long tempNumber = 0;
                if (!int.TryParse(args[0], out tempThreads))
                {
                    Console.WriteLine("Thread count must be a number");
                    return;
                }
                if (!long.TryParse(args[1], out tempNumber))
                {
                    Console.WriteLine("Total number isn't a number");
                    return;
                }
                if (tempThreads > NumberOfThreads || tempThreads < 1)
                {
                    Console.WriteLine("Invalid number of threads, must be a value from 1 to " + NumberOfThreads + " (total threads in this system)");
                    return;
                }
                if(tempNumber < 2){
                    Console.WriteLine("Number must bigger than 1");
                    return;
                }
                NumberOfThreads = tempThreads;
                number = tempNumber;
            }
            Console.WriteLine("Running on " + NumberOfThreads + " threads");
            Console.WriteLine("Total numbers to check: " + number);
            //magic
            NumberOfThreads = (NumberOfThreads == NumberOfThreadsThreshold) ? NumberOfThreads - 1 : (NumberOfThreads > NumberOfThreadsThreshold) ? (int)(NumberOfThreads * 1.1) : NumberOfThreads;
            Primes(number);
        }

        static void Primes(long max)
        {
            Stopwatch sw = new Stopwatch();
            sw.Start();
            List<Thread> threads = new List<Thread>();
            List<List<long>> threadNumbers = new List<List<long>>();
            List<long> primeCounting = new List<long>();
            long totalTime = 0;
            for (int i = 0; i < NumberOfThreads; i++)
            {
                primeCounting.Add(0);
                threadNumbers.Add(new List<long>());
            }
            threadNumbers[0].Add(2);
            int currentThread = (NumberOfThreads > 1) ? 1 : 0;
            for (long i = 3; i <= max; i += 2)
            {
                threadNumbers[currentThread].Add(i);
                currentThread = (currentThread >= NumberOfThreads - 1) ? 0 : currentThread + 1;
            }
            for (int index = 0; index < NumberOfThreads; index++)
            {
                Thread newThread = new Thread(PrimesThreadLoop);
                threads.Add(newThread);
                threads[index].Start(new PassthroughParams(primeCounting, threadNumbers[index], index));
            }
            foreach (Thread thread in threads)
                thread.Join();
            sw.Stop();
            totalTime = sw.ElapsedMilliseconds;
            long totalPrimeCount = 0;
            foreach (long prime_count in primeCounting)
                totalPrimeCount += prime_count;
            Console.WriteLine("Prime numbers found: " + totalPrimeCount);
            Console.WriteLine("Time elapsed: " + totalTime + "ms");
        }

        static void PrimesThreadLoop(object? parameters)
        {
            if (parameters is null)
                return;
            PassthroughParams passthroughParams = (PassthroughParams)parameters;
            long primeCounter = 0;
            foreach (long number in passthroughParams.numbers)
                if (IsPrime(number))
                    primeCounter++;
            passthroughParams.primeCounter[passthroughParams.index] = primeCounter;
        }

        static bool IsPrime(long number)
        {
            for (int divisor = 2; divisor <= number / 2; divisor++)
                if (number % divisor == 0)
                    return false;
            return true;
        }
    }

    public class PassthroughParams
    {
        public List<long> numbers = new List<long>();
        public List<long> primeCounter = new List<long>();
        public int index;

        public PassthroughParams(List<long> primeCounter, List<long> numbers, int index)
        {
            this.numbers = numbers;
            this.primeCounter = primeCounter;
            this.index = index;
        }
    }
}