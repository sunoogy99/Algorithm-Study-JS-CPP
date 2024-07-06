const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let M = null;

let countN = 0;
let board = [];

const solution = (N, M, board) => {
    
    // 시작 지점 x, y를 주면 몇 개를 바꿔야 하는지 검사하는 함수
    const checkChangeCount = (x, y) => {
        let changeCountBaseStart = 0;
        let changeCountBaseStartReverse = 0; // 처음 칸을 다르게 시작하는 경우
        
        // 시작점의 색과 가로, 세로 얼마만큼 칸수를 이동했는지 여부에 따라 색깔 변경 여부 파악
        for (let i = x; i < x + 8; i++) {
            for (let j = y; j < y + 8; j++) {
                if (board[i][j] === board[x][y]) {
                    if (((i - x) % 2 === 0 && (j - y) % 2 !== 0) || ((i - x) % 2 !== 0 && (j - y) % 2 === 0)) {
                        changeCountBaseStart++;
                    } 
                } else {
                    if (((i - x) % 2 !== 0 && (j - y) % 2 !== 0) || ((i - x) % 2 === 0 && (j - y) % 2 === 0)) {
                        changeCountBaseStart++;
                    }
                }
            }
        }

        // 처음 칸을 다르게 시작하는 경우도 세봐야 함. 시작 지점을 고치는게 더 빠른 경우도 있음
        for (let i = x; i < x + 8; i++) {
            for (let j = y; j < y + 8; j++) {
                if (board[i][j] === board[x][y]) {
                    if (((i - x) % 2 !== 0 && (j - y) % 2 !== 0) || ((i - x) % 2 === 0 && (j - y) % 2 === 0)) {
                        changeCountBaseStartReverse++;
                    }
                } else {
                    if (((i - x) % 2 === 0 && (j - y) % 2 !== 0) || ((i - x) % 2 !== 0 && (j - y) % 2 === 0)) {
                        changeCountBaseStartReverse++;
                    } 
                }
            }
        }
        
        return Math.min(changeCountBaseStart, changeCountBaseStartReverse);
    }

    let ans = Math.min();

    for (let i = 0; i <= N - 8; i++) {
        for (let j = 0; j <= M - 8; j++) {
            let cnt = checkChangeCount(i, j);
            
            if (cnt < ans) {
                ans = cnt;
            }
        }
    }

    return ans;
}

rl.on('line', (line) => {
    if (!N && !M) {
        [N, M] = line.split(' ').map(e => +e);
    } else {
        board.push(line.split(''));
        countN++;
    }

    if (countN === N) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, M, board);
    console.log(res);
    process.exit();
});