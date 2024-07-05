const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let numbers = [];

const solution = (numbers) => {
    let answer = [];
    for (let i = 0; i < numbers.length - 1; i++) {
        for (let j = i + 1; j < numbers.length; j++) {
            answer.push(numbers[i] + numbers[j]);
        }
    }

    answer = Array.from(new Set(answer)).sort((a, b) => a - b);
    // answer = [...new Set(answer)].sort((a, b) => a - b);
    return answer;
}

rl.on('line', (line) => {
    numbers = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(numbers);
    console.log(res);
    process.exit();
});