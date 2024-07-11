const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let K = null;

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

    isEmpty() {
        return this.front === null && this.rear === null;
    }

    enqueue(item) {
        const newNode = new Node(item);
        if (this.isEmpty()) this.front = newNode;
        else this.rear.next = newNode;
        this.rear = newNode;
    }

    dequeue() {
        if (this.isEmpty()) return;
        const peekNode = this.front.data;
        this.front = this.front.next;
        if (!this.front) this.rear = null;
        return peekNode;
    }

    peek() {
        if (this.isEmpty()) return -1;
        return this.front.data;
    }
}

const solution = (N, K) => {
    // 주의) let dp = Array(100001).fill([Math.min(), 0]); -> fill로 선언 시 같은 객체를 참조하게 됨
    // 따라서 dp[pos][0] = 5;를 할당하면 모든 인덱스 값이 [5, 0]이 됨

    let dp = Array.from(Array(100001), () => [Math.min(), 0]);
    const inRange = (pos) => pos >= 0 && pos <= 100000;

    const bfs = (pos) => {
        const queue = new Queue();
        dp[pos] = [0, 0];
        queue.enqueue(pos);

        while (!queue.isEmpty()) {
            let curPos = queue.dequeue();
            let visitCount = dp[curPos][0];

            // 이전 숨바꼭질 1에서는 < 부등호 사용하였으나, 숨바꼭질 2에서는 같은 경우라면 방법 1가지가 더 존재하는 것
            // 방법의 수도 세야 하기 때문에 같은 경우에도 Queue 탐색할 포지션에 넣음     
            if (inRange(curPos - 1) && visitCount + 1 <= dp[curPos - 1][0]) {
                dp[curPos - 1][0] = visitCount + 1;
                dp[curPos - 1][1] += 1;
                queue.enqueue(curPos - 1);
            }

            if (inRange(curPos + 1) && visitCount + 1 <= dp[curPos + 1][0]) {
                dp[curPos + 1][0] = visitCount + 1;
                dp[curPos + 1][1] += 1;
                queue.enqueue(curPos + 1);
            }

            if (inRange(curPos * 2) && visitCount + 1 <= dp[curPos * 2][0]) {
                dp[curPos * 2][0] = visitCount + 1;
                dp[curPos * 2][1] += 1;
                queue.enqueue(curPos * 2);
            }
        }
    }

    bfs(N);
    if (N === K) return 0 + '\n' + 1; // (히든 케이스) 같은 자리인 경우 가만히 있는 방법 1가지 존재
    return dp[K][0] + '\n' + dp[K][1];
}

rl.on('line', (line) => {
    if (!N && !K) {
        [N, K] = line.split(' ').map(e => +e);
    } 

    rl.close();    
}).on('close', () => {
    const res = solution(N, K);
    console.log(res);
    process.exit();
});