const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class Queue {
    constructor() {
        this.front = null;
        this.rear = null;
    }

    enqueue(item) {
        const newNode = new Node(item);
        if (this.front === null) this.front = newNode;
        else this.rear.next = newNode;
        this.rear = newNode;
    }

    dequeue() {
        if (this.isEmpty()) return -1;
        const dequeueNum = this.front.data;
        this.front = this.front.next;
        if (this.front === null) this.rear = null;
        return dequeueNum;
    }

    isEmpty() {
        return this.front === null && this.rear === null;
    }
}

let N = null;

const solution = (N) => {
    let dp = Array(N + 1).fill(Math.min());

    const inRange = (num) => num >= 1 && num <= N;

    // N을 1로 만들기 위한 최소 연산 수 구하기
    // === 1을 N으로 만들기 위한 최소 연산 수 구하기
    const q = new Queue();
    q.enqueue(1);
    dp[1] = 0;

    while (!q.isEmpty()) {
        let num = q.dequeue();

        if (inRange(num * 3) && dp[num] + 1 < dp[num * 3]) {
            dp[num * 3] = dp[num] + 1
            q.enqueue(num * 3);
        }

        if (inRange(num * 2) && dp[num] + 1 < dp[num * 2]) {
            dp[num * 2] = dp[num] + 1;
            q.enqueue(num * 2);
        }

        if (inRange(num + 1) && dp[num] + 1 < dp[num + 1]) {
            dp[num + 1] = dp[num] + 1;
            q.enqueue(num + 1);
        }
    }

    return dp[N];
}

rl.on('line', (line) => {
    N = +line;
    rl.close();
}).on('close', () => {
    const res = solution(N);
    console.log(res);
    process.exit();
});