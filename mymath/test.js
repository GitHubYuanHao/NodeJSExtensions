// test.js
const createObject = require('./mymath.node');

const obj = createObject(10);
console.log("10 + 1 = ", obj.plusOne());
console.log("11 + 1 = ", obj.plusOne());
console.log("12 + 1 = ", obj.plusOne());

const obj2 = createObject(20);
console.log("20 + 1 = ", obj2.plusOne());
console.log("21 + 1 = ", obj2.plusOne());
console.log("22 + 1 = ", obj2.plusOne());

console.log("5 + 2 = ", obj.Add(5, 2));
console.log("5 - 2 = ", obj.Sub(5, 2));
console.log("5 * 2 = ", obj.Mul(5, 2));
console.log("5 / 2 = ", obj.Div(5, 2));

