# List a remote app's widget tree (names and classes only)

import sys
import string

from Tkinter import *

def listtree(master, app):
	list = Listbox(master, {'name': 'list',
				Pack: {'expand': 1, 'fill': 'both'}})
	listnodes(list, app, '.', 0)
	return list

def listnodes(list, app, widget, level):
	klass = list.send(app, 'winfo', 'class', widget)
##	i = string.rindex(widget, '.')
##	list.insert('end', '%s%s (%s)' % ((level-1)*'.   ', widget[i:], klass))
	list.insert('end', '%s (%s)' % (widget, klass))
	children = list.tk.splitlist(
		list.send(app, 'winfo', 'children', widget))
	for c in children:
		listnodes(list, app, c, level+1)

def main():
	if not sys.argv[1:]:
		sys.stderr.write('Usage: listtree appname\n')
		sys.exit(2)
	app = sys.argv[1]
	tk = Tk()
	tk.minsize(1, 1)
	f = Frame(tk, {'name': 'f', Pack: {'expand': 1, 'fill': 'both'}})
	list = listtree(f, app)
	tk.mainloop()

if __name__ == '__main__':
	main()
