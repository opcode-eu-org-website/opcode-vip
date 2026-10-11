**This is source code repo for [vip.opcode.eu.org](https://vip.opcode.eu.org)**

## Licence

	Copyright (c) 2003-2019 Robert Ryszard Paciorek <rrp@opcode.eu.org>
	
	To jest wolny i otwarty dokument/oprogramowanie. Redystrybucja,
	użytkowanie i/lub modyfikacja SĄ DOZWOLONE na warunkach licencji MIT.
	
	This is free and open document/software. Redistribution, use
	and/or modify ARE PERMITTED under the terms of the MIT license. 

### The MIT Licence

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	 
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	 
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

## Build

### make way

1. run `make init` in main dir of this repo
2. run `sudo make installDependencies` in main dir of this repo
3. run `make all` to build all documents
4. results will be write into `output-www` directory

You can also build single document by run `make dokumentName` in source dir for this document (for example `cd vademecum; make vademecum`).

### act way

You can use [act](https://github.com/nektos/act) to locally run [`.github/workflows/deploy.yml`](.github/workflows/deploy.yml)

1. run `act --reuse` in main dir of this repo
2. use `docker cp` to copy output directory (`output-www`) from container to host system.
