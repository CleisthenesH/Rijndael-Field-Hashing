**Under Construction**

# Rijndael Field Hashing

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/5/53/Evariste_galois.jpg" alt="A drawing of the mathematician Galos" width = 300px>
    <a href="https://en.wikipedia.org/wiki/%C3%89variste_Galois">
	<br>
	    A depiction of a 15 years olf Galois from wikimedia commons.
	        <br>
		    (Oddly the most common depiction of Galois and flipped horizontally from the original drawing).
  </a>
</p>

The Rijndael Field is a name for the Galois Field of order $2^8$
What's makes this field interesting is that the natural mapping between a byte of memory and an element of the field.
Since most numeric algorithm on $\mathbb{R}$ only require field operations they are can be easily applied to the Rijndael Field, and hence operations on bytes and hashing in particular.

This observation isn't novel as the name Rijndael is a portmanteau of the Belgian cryptographers Joan Daemen and Vincent
Rijmen last names, who used this observation to make the algorithm selected Advanced Encryption Standard in 2001.

# A Taste of What's to Come
Assume for now that whatever the equivalent to addition, multiplication, and division in $\mathbb{R}$ are computationaly tractable in GF $(2^8)$.Then the application Gaussian elimination also works in GF $(2^8)$, meaning we can invert matrices.
In particular, given $n$ vectors $x_k$ with $n$ elements and $n$ targets $y_k$ we can find $n$ coefficients $a$ such that:

$$ y_k = a\cdot x_k $$

# Structure of this Repository
The goal of this repository is to have a src folder the implementation of algorithms in C, and a docs folder with explanations written in LaTeX. 
