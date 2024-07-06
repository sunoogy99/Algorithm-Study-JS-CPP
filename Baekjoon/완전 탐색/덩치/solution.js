const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let count = 0;
let people = [];

const solution = (N, people) => {
    const ranks = [];
    for (let i = 0; i < people.length; i++) {
        let rank = 1;
        let [curW, curH] = people[i];

        for (let j = 0; j < people.length; j++) {
            if (i === j) continue;
            let [comW, comH] = people[j];

            if (comW > curW && comH > curH) {
                rank++;
            }
        }

        ranks.push(rank);
    }

    return ranks.join(' ');
}

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else {
        people.push(line.split(' ').map(e => +e));
        count++;
    }

    if (count === N) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, people);
    console.log(res);
    process.exit();
});