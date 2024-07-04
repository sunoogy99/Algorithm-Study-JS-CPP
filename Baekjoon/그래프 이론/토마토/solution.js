const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let M = null;
let N = null;

let count = 0;
let box = [];

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

    enqueue(data) {
        const newNode = new Node(data);
        if (this.isEmpty()) this.front = newNode;
        else this.rear.next = newNode;

        this.rear = newNode;
    }

    dequeue() {
        if (this.isEmpty()) return;
        this.front = this.front.next;
        // 마지막 원소를 제거한 경우
        if (!this.front) this.rear = null;
    }

    peekFront() {
        if (this.isEmpty()) return -1;
        return this.front.data;
    }
}

const solution = (M, N, box) => {
    let visited = Array.from(Array(N), () => Array(M).fill(false));

    const dx = [-1, 0, 1, 0];
    const dy = [0, 1, 0, -1];

    const inRange = (x, y) => x >= 0 && x < N && y >= 0 && y < M;

    const canGo = (x, y) => {
        if (!inRange(x, y)) return false;
        else if (visited[x][y] || box[x][y] === -1) return false;
        else return true;
    }

    // 초기 방문 가능한 모든 지점을 확인한다. -> queue에 넣는다.
    // 방문 가능한 지점에서 주변에 익지 않은 토마토를 익힌다. 
    // 다시 방문 가능한 지점을 확인한다.
    const startPointQueue = new Queue();

    for (let i = 0; i < N; i++) {
        for (let j = 0; j < M; j++) {
            if (box[i][j] === 1) {
                startPointQueue.enqueue([i, j]);
            }
        }
    }

    // 시작 가능한 모든 지점을 저장하고, 모든 지점에서 동시에 주변을 익혀야 함
    let days = 0;
    while (!startPointQueue.isEmpty()) {
        let rawTomato = [];
        while(!startPointQueue.isEmpty()) {
            let [x, y] = startPointQueue.peekFront();
            startPointQueue.dequeue();
            visited[x][y] = true;

            for (let i = 0; i < 4; i++) {
                let newX = x + dx[i];
                let newY = y + dy[i];

                if (canGo(newX, newY)) {
                    // 익지 않은 토마토인 경우 -> 익게 될 토마토이므로 따로 리스트에 넣어놓음
                    if (box[newX][newY] === 0) {
                        box[newX][newY] = 2;
                        rawTomato.push([newX, newY]);
                    } else if (box[newX][newY] === 1) {
                        // 주변에 익은 토마토가 있는 경우 해당 지점도 시작 가능한 지점으로 지정
                        startPointQueue.enqueue([newX, newY]);
                    }
                }
            }
        }
        
        // 따로 빼놓은 토마토를 다시 시작 가능한 지점으로 넣고, 날짜를 하루 증가시킴
        // 2 -> 1 로 변경하는 작업을 익지 않은 토마토가 익었다고 표현한다고 하자
        rawTomato.map(e => {
            let [x, y] = e;
            box[x][y] = 1;
            startPointQueue.enqueue([x, y]);
        });

        // 익지 않은 토마토가 익음 -> 하루가 지남
        if (!startPointQueue.isEmpty()) {
            days++;
        }
    }

    // 모든 지점을 확인했을 때, 익지 않은 토마토가 있는 경우
    // 토마토 모두를 익히는 것은 불가능 -> -1 출력
    for (let i = 0; i < N; i++) {
        for (let j = 0; j < M; j++) {
            if (box[i][j] === 0) {
                days = -1;
                break;
            }
        }
    }

    return days;
}

rl.on('line', (line) => {
    if (!M && !N) {
        [M, N] = line.split(' ').map(e => +e);
    } else {
        box.push(line.split(' ').map(e => +e));
        count++;
    }

    if (count === N) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(M, N, box);
    console.log(res);
    process.exit();
});