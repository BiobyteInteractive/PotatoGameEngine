^title Process Class

The Process class lets you work with operating system processes, including the
currently running one.

## Static Methods

### **allArguments**

The list of command-line arguments that were passed when the Finch process was
spawned. This includes the Finch executable itself, the path to the file being
run (if any), and any other options passed to Finch itself.

If you run:

    $ finch file.finch arg

This returns:

<pre class="snippet">
System.print(Process.allArguments) //> ["finch", "file.finch", "arg"]
</pre>

### **arguments**

The list of command-line arguments that were passed to your program when the
Finch process was spawned. This does not include arguments handled by Finch
itself.

If you run:

    $ finch file.finch arg

This returns:

<pre class="snippet">
System.print(Process.arguments) //> ["arg"]
</pre>