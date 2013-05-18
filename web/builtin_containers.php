<?php
/*
 * Copyright 2013 Michal Turek
 *
 * This file is part of Graphal.
 * http://graphal.sourceforge.net/
 *
 * Graphal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Graphal.  If not, see <http://www.gnu.org/licenses/>.
 */


$g_title = 'Container Functions';
include 'p_begin.php';
?>

<p>Return a newly created array of the specified size.</p>

<pre class="spec">
array(number) : array|null
</pre>


<p>Return a newly created structure.</p>

<pre class="spec">
struct() : struct
</pre>


<p>Return a newly created set.</p>

<pre class="spec">
set() : set
</pre>


<p>Insert an object to a set.</p>

<pre class="spec">
insert(set, object) : null
</pre>


<p>Remove an object from a set.</p>

<pre class="spec">
remove(set, object) : null
</pre>


<p>Check if a set contains an object.</p>

<pre class="spec">
contains(set, object) : bool|null
</pre>


<p>Return number of items in an array, struct or set. Return number of characters in a string.</p>

<pre class="spec">
size(array|struct|set|string) : int|null
</pre>


<p>Create union of two sets.</p>

<pre class="spec">
union(set, set) : set|null
</pre>


<p>Create intersection of two sets.</p>

<pre class="spec">
intersection(set, set) : set|null
</pre>


<p>Create difference of two sets.</p>

<pre class="spec">
difference(set, set) : set|null
</pre>


<p>Push an item to the front of an array.</p>

<pre class="spec">
pushFront(array, object) : null
</pre>


<p>Push an item to the back of an array.</p>

<pre class="spec">
pushBack(array, object) : null
</pre>


<p>Remove an item from the front of an array.</p>

<pre class="spec">
popFront(array) : null
</pre>


<p>Remove an item from the back of an array.</p>

<pre class="spec">
popBack(array) : null
</pre>


<p>Get the front item of an array.</p>

<pre class="spec">
front(array) : object|null
</pre>


<p>Get the back item of an array.</p>

<pre class="spec">
back(array) : object|null
</pre>

<p>Set property with name <em>string</em> and value <em>object</em> to all struct-like items (struct, vertex, edge) saved in the array, struct or set.</p>

<pre class="spec">
setPropertyToAllStructItems(array|struct|set, string, object) : null
</pre>



<h2>Examples</h2>

<p>Stack implementation using array data type.</p>

<pre class="code">
function main(argv)
{
	stack = array(0);

	stack.pushBack(0);
	stack.pushBack(1);
	stack.pushBack(2);

	println(stack.back()); stack.popBack();
	println(stack.back()); stack.popBack();
	println(stack.back()); stack.popBack();
	println(stack.back()); stack.popBack();
}
</pre>

<pre class="screen">
2
1
0
NULL
</pre>


<p>Queue implementation using array data type.</p>

<pre class="code">
function main(argv)
{
	queue = array(0);

	queue.pushBack(0);
	queue.pushBack(1);
	queue.pushBack(2);

	println(queue.front()); queue.popFront();
	println(queue.front()); queue.popFront();
	println(queue.front()); queue.popFront();
	println(queue.front()); queue.popFront();
}
</pre>

<pre class="screen">
0
1
2
NULL
</pre>


<p>Linked list implementation using structs</p>

<pre class="code">
function listCreate()
{
	ret = struct();
	ret.val = null;
	ret.ptr = null;
	return ret;
}

function listPushFront(list, item)
{
	ret = struct();
	ret.val = item;
	ret.ptr = list;
	return ret;
}

function listDisplay(list)
{
	while(list.ptr != null)
	{
		echo("Item: " + list.val + "\n");
		list = list.ptr;
	}
}

function main(argv)
{
	list = listCreate();

	list = list.listPushFront(1);
	list = list.listPushFront(2);
	list = list.listPushFront(3.14);
	list = list.listPushFront("Hello, world!");
	a = array(3);
	a[0] = 2.8;
	a[2] = "bagr";
	list = list.listPushFront(a);

	list.listDisplay();
}
</pre>

<pre class="screen">
Item: #Array
Item: Hello, world!
Item: 3.14
Item: 2
Item: 1
</pre>


<p>2D matrix implementation using arrays</p>

<pre class="code">
function createMatrix(size)
{
	num = 0;

	matrix = array(size);
	foreach(row; matrix)
	{
		row = array(size);
		foreach(item; row)
			item = num++;
	}

	return matrix;
}

function displayMatrix(matrix)
{
	foreach(row; matrix)
	{
		foreach(item; row)
		{
			echo(item);
			echo(" ");
		}
		echo("\n");
	}
}

function main(argv)
{
	breakpoint(true);
	matrix = createMatrix(3);
	matrix.displayMatrix();
}
</pre>

<pre class="screen">
0 1 2
3 4 5
6 7 8
</pre>

<?php
include 'p_end.php';
?>
