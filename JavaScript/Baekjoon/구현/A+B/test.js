const solution = require('./solution');

describe('solution function: A + B', () => {
    test('adds 1 + 2 to equal 3', () => {
        const result = solution(1, 2);
        expect(result).toBe(3);
    });

    test('adds 4 + 5 to equal 9', () => {
        const result = solution(4, 5);
        expect(result).toBe(9);
    });
});