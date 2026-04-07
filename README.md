# OldBasic

OldBasic is a BASIC interpreter intended to be used for running the programs found in the [Usborne 1980s Computer Books](https://usborne.com/us/books/computer-and-coding-books).

I remember these books from when I was in primary school (elementary school) and although I loved flicking through them and imagining how the games would play if I typed them out, I don't recall actually ever typing one out back then!

Anyway, I learned they were available for download when watching a Youtube video by Kari Lawler called [Programming Retro Games in Python](https://www.youtube.com/watch?v=3kdM9wyglnw) and I thought while it looked fun to do it in Python it might be more fun to write a BASIC interpeter to run them with minimal updates and experience writing with line numbers again.

Shortly after I started I realized that I wanted the programs to be able to run with emojis in the text strings so I've taken care to ensure that emojis work as both inputs and outputs. In that way we can also embellish the original programs with emojis which I think adds a little decorative flair.

My goal is to allow for the programs in the Usborne Books to run without modification after being typed out, however there is one situation where I decided that it was better to rely on a specific alteration rather than trying to infer behavior. And that it in the busy loops the programs use to emulate sleep on those older computers. Any busy loop on a modern computer finishes in microseconds and is ineffective at slowing the program so I have introduced a SLEEP command to allow for a suitable sleep interval to be specified. It isn't necessary to remove the busy loop entirely, just add the SLEEP with an interval divided by the loop count to a line number in between the busy loop lines.

Thank you to the writers, illustrators, and staff at Usborne Books for creating these books and making them available for download. And thank you to Kari Lawler for making me aware of them.

- Fredrick Pennachi
