const SDRM = require("../lib/binding.js");
const assert = require("assert");

assert(SDRM, "The expected function is undefined");

function testBasic()
{
    const result = SDRM("steam_api64.dll", 00000000);
    console.log(result);
    //assert.strictEqual(result, "world", "Unexpected value returned");
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");

console.log("Tests passed- everything looks OK!");