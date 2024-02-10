
import Module from '../../build/bin/minivm.js';
import Emception from "./emception.js";
import wasmBinary from '../../build/bin/minivm.wasm';

const wasmBuffer = await (await fetch(wasmBinary)).arrayBuffer();
console.log(wasmBuffer);

const emception = new Emception();
window.emception = emception;
await emception.init();

emception.run('emcc --check -Wno-version-check');

emception.onstdout = (str) => console.log(str);
emception.onstderr = (str) => console.error(str);
export const run = (src) => {
    let comps = 0;
    
    const mod = Module({
        noInitialRun: true,
        wasmBinary: wasmBuffer,
    });

    mod._vm_compile_c_to_wasm = (n) => {
        comps += 1;
        const cBuf = new TextDecoder().decode(mod.FS.readFile(`/in${n}.c`));
        console.log(cBuf);
        emception.fileSystem.writeFile(`/working/in${comps}.c`, cBuf);
        const result = emception.run(`emcc -O3 -s EXPORT_ALL=1 -s SIDE_MODULE=1 /working/in${comps}.c -o /working/out${comps}.wasm -Wno-version-check -Wno-incompatible-library-redeclaration -Wno-parentheses-equality`);
        if (result.returncode !== 0) {
            console.error(`emcc exited with code ${result.returncode}`)
        }
        const soBuf = emception.fileSystem.readFile(`/working/out${comps}.wasm`);
        mod.FS.writeFile(`/out${n}.so`, soBuf);
    };

    mod.callMain(['-e', src]);
};
