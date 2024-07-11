const solution = () => {
    let visited = Array(10001).fill(false);

    // 완전 탐색이지만 방문 체크를 통해 방문 횟수를 최소화함
    const d = (num) => {
        let next = (num + "").split('').map(e => +e).reduce((prev, curr) => prev + curr, num);

        if (next <= 10000 && !visited[next]) {
            visited[next] = true;
            d(next);
        }
    }

    for (let i = 1; i <= 10000; i++) {
        if (!visited[i]) {
            d(i);
        }
    }

    // 10001만큼 배열을 만들어서 맨 처음 칸은 제거해야 함
    return visited.slice(1).reduce((prev, curr, i) => prev + (curr ? '' : i + 1 + '\n'), '');
}

const res = solution();
console.log(res);