class Main extends FibonacciCalculator{
    public static void main(String[] args){
        calculator = new FibonacciCalculator();
        int fib11 = calculator.calculateFibonacci(11);
        System.out.println("Fib(11) is "+fib11);
    }
}