const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let count = 0;
let pixels = [];

const solution = (N, pixels) => {
    let visited = Array.from(Array(N), () => Array(N).fill(false));
    
    const dx = [-1, 0, 1, 0];
    const dy = [0, 1, 0, -1];

    const inRange = (x, y) => x >= 0 && x < N && y >= 0 && y < N;
    const canGo = (x, y, color) => {
        if (!inRange(x, y)) return false;
        else if (visited[x][y] || pixels[x][y] !== color) return false;
        else return true;
    }

    const bfs = (x, y, color) => {
        const queue = [];
        queue.push([x, y]);

        while (queue.length !== 0) {
            let [curX, curY] = queue.shift();

            for (let i = 0; i < 4; i++) {
                let newX = curX + dx[i];
                let newY = curY + dy[i];

                if (canGo(newX, newY, color)) {
                    queue.push([newX, newY]);
                    visited[newX][newY] = true;
                }
            }
        }
    }

    let searchColor = ['G', 'R', 'B'];
    let RGBpartitions = 0;

    for (const color of searchColor) {
        for (let i = 0; i < N; i++) {
            for (let j = 0; j < N; j++) {
                if (canGo(i, j, color)) {
                    bfs(i, j, color);
                    RGBpartitions++;
                }
            }
        }
    }

    // visited 배열 초기화 
    visited = visited.map(row => row.map(e => false));
    pixels = pixels.map(row => row.map(e => e = e === 'G' ? 'R' : e));
    let RBpartitions = 0;

    for (const color of searchColor.slice(1)) {
        for (let i = 0; i < N; i++) {
            for (let j = 0; j < N; j++) {
                if (canGo(i, j, color)) {
                    bfs(i, j, color);
                    RBpartitions++;
                }
            }
        }
    }

    return RGBpartitions + ' ' + RBpartitions;
}

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else {
        pixels.push(line.split(''));
        count++;
    }

    if (count === N) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, pixels);
    console.log(res);
    process.exit();
});