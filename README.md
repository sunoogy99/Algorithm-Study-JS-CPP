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

    test('test case', () => {
        expect(solution(1, 2).toBe(3)); // 예시 테스트 케이스
    });
    ```
5. Docker 이미지 빌드 및 실행하기
    ```
    docker build -t algorithm-study .
    docker run --rm algorithm-study
    ```
6. Git Commit 메시지 남기기
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