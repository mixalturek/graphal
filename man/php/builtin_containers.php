<?php
$g_title = 'Container functions';
include 'p_begin.php';
?>

<p>Return newly created array of the specified size.</p>

<pre class="spec">
array(number) : array|null
</pre>


<p>Return newly created structure.</p>

<pre class="spec">
struct() : struct
</pre>


<p>Return size of the array or string lenght.</p>

<pre class="spec">
size(array|string) : int|null
</pre>


<p>Push the item to the front of the array.</p>

<pre class="spec">
pushFront(array, object) : null
</pre>


<p>Push the item to the back of the array.</p>

<pre class="spec">
pushBack(array, object) : null
</pre>


<p>Remove item from the front of the array.</p>

<pre class="spec">
popFront(array) : null
</pre>


<p>Remove item from the back of the array.</p>

<pre class="spec">
popBack(array) : null
</pre>


<p>Get the front item of the array.</p>

<pre class="spec">
front(array) : object|null
</pre>


<p>Get the back item of the array.</p>

<pre class="spec">
back(array) : object|null
</pre>



<h3>Examples</h3>

<p>Stack implementation using arrays</p>

<pre class="code">
a = array(0);
a.pushBack(0);
a.pushBack(1);
a.pushBack(2);
a.popBack();

for(i = 0; i &lt; a.size(); ++i)
	println(a[i]);
</pre>

<pre class="screen">
0
1
</pre>


<p>Queue implementation using arrays</p>

<pre class="code">
a = array(0);
a.pushFront(0);
a.pushFront(1);
a.pushFront(2);
a.popBack();

for(i = 0; i &lt; a.size(); ++i)
	println(a[i]);
</pre>

<pre class="screen">
2
1
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
