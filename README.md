# Algorithm-Study-JS

## Solve with JavaScript ##
- **START** - *24.06.27*

## How to Study?
1. 문제를 제공하는 사이트에 맞는 디렉토리 선택하기

2. 문제 유형 디렉토리 선택하기

3. 문제 이름으로 디렉토리 만들기

4. **solution.js, test.js** 파일 생성하여 문제 해결 코드와 테스트 코드 작성하기
    ```javascript
    // solution.js 예시
    function solution(a, b) {
        return a + b; 
    }

    module.exports = solution;
    ```
    ```javascript
    // test.js 예시
    const solution = require('./solution');

    describe('solution function test', () => {
        test('test case 1', () => {
            expect(solution(1, 2).toBe(3)); // 예시 테스트 케이스
        });
        
        test('test case 2', () => {
            expect(solution(3, 4).toBe(7)); // 예시 테스트 케이스
        });
    })
    ```
5. ~~Docker 이미지 빌드 및 실행하기~~ -> 이미지 빌드하려 했으나 로컬에 Jest 설치하는 방식으로 적용...
    ```javascript
    // docker build -t algorithm-study .
    // docker run --rm algorithm-study
    npm install --save-dev jest
    ```
6. 문제 디렉터리에서 solution.js, test.js 실행하기
    ```javascript
    node solution.js // solution.js 실행
    npm test // test.js 실행
    ```
7. Git Commit 메시지 남기기
- **풀이한 상태를 명확하게 기록한다.**
- 혼자 힘으로 푼 경우, ✅
- 다른 코드를 참조한 경우, ⚠️
- 풀지 못한 경우, ❌
    ```
    git add .
    git commit -m "[백준] [구현] A+B ✅ (24.06.27)"
    ```

7. Github Repository로 push하기
    ```
    git push origin main
    ```
---
## Node.js 입출력 
### **기본 readline 설정하기**
```javascript
// readline 모듈
const readline = require('readline');

// 입출력 인터페이스 설정
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

rl.on('line', (line) => {
    /* 
        한 줄씩 입력
        입력 받은 값은 line에 저장됨
    */
    rl.close(); // 생략 시 입력 무한으로 받을 수 있음
});

rl.on('close', () => {
    /*
        입력 종료 시 실행되는 코드
    */
    process.exit();
});
```

### **한 줄 입력**
- case ) 1 2
```javascript
let data = [];

rl.on('line', (line) => {
    data = line.split(' ').map(e => +e);
});

rl.on('close', () => {
    solution(data[0], data[1]);
    process.exit();
});
```

### **여러 줄 입력**
- case ) 
    - 2
    - 0 2
    - 1 2 3
    - 4 5 6
    - 7 8 9
```javascript
let N = null;
let info = null;
let count = 0;
const data = [];

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else if (!info) {
        info = line.split(' ').map(e => +e);
    } else {
        data.push(line);
        count += 1;
    }

    if (count === N) {
        rl.close();
    }
});

rl.on('close', () => {
    solution(N, info, data);
    process.exit();
});
```

### **FileSystem 기반 한 줄 입력**
- ~~백준은 파일 입출력으로 받는 것이 성능이 더 좋다고 한다.~~
- 백준에서 아래 방법대로 할 경우, Windows 상에서는 /dev/stdin 경로를 따르지 않음
- 로컬에서 테스트하기 번거로운 부분이 존재함
```javascript
const fs = require('fs');
let input = fs.readFileSync('/dev/stdin').toString().split('\n');

console.log(input);
```

### **FileSystem 기반 여러 줄 입력**
- case )
    - 3
    - 1 3 2
    - 5 6 1
    - 9 7 2
```javascript
let fs = require('fs');
let input = fs.readFileSync('/dev/stdin').toString().split('\n');

const N = +input[0];
const data = [];

for (let i = 1; i < N + 1; i++) {
    data.push(input[i].split(' ').map(e => +e));
}

solution(N, data);
```
- case )
    - 3
    - 1 2
    - 5 3 1
    - 6 4 9
    - 7 5 3
```javascript
const solution = (N, info, data) => {
    const [X, Y] = info; // 구조 분해 할당
    // 로직 작성
}

let fs = require('fs');
let input = fs.readFileSync('/dev/stdin').toString().split('\n');

const N = +input[0];
const info = input[1].split(' ').map(e => +e);
const data = [];

for (let i = 2; i < N + 2; i++) {
    data.push(input[i].split(' ').map(e => +e));
}
```

## Reference
### **Node.js 입력 받는 방법**

https://velog.io/@grap3fruit/%EA%B5%AC%EB%A6%84goorm-%EC%BD%94%ED%85%8C-javascript-%EB%A1%9C-%EC%9E%85%EB%A0%A5%EA%B0%92-%EB%B0%9B%EB%8A%94-%EB%B0%A9%EB%B2%95