Text Document Template Parser and Processor

This file describes three possible ways to use the TDTPP library.  These 
methods are:

  1) Simple

  2) Advanced

  3) Combination


----------------------
Simple Method
----------------------

The simplest way to use the TDTPP library is to link your program with
libtemplates.a.  To parse a template, declare two char* arrays.  The first
array consists of the names of tokens in your file, and the second consists of
the values that correspond to the token names.  Terminate the list of tokens
with a NULL.  For example:

   char* tokens[] = { "one", "two", "three", NULL };
   char* values[] = { "red", "green", "blue" };

This says that the value of "one" is "red", "two" is "green", etc.  Once you
have declared the tokens and values, you simply need to call ToHTML2 to
process the template, as follows:

   ToHTML2( "mytemplate.tem", tokens, values, 0 );

The last '0' in that call is the 'mode'.  If you want the HTTP headers to be
printed, set the last parameter to HTML_HEADER.  You can 'or' other values
together to configure the behavior of ToHTML2:

  HTML_HEADER - print the HTTP headers (content-type, etc.).
  HTML_NO_CACHE - print additional headers (if HTML_HEADER is set) to prevent
    browsers from caching the resulting page.
  HTML_LEGACY_SUPPORT - enable support of 'legacy' tags.  By default, legacy
    tags are not parsed.  The legacy tags are listed in the section at the end
    of this document.

----------------------
Advanced Method
----------------------

The advanced method takes advantage of the TDTPP API directly.  Doing say is
more cumbersome than ToHTML2 for most programs, but allows greater flexibility
(query tokens, etc.).

To begin, you must declare a variable of type 't_ae_template_mgr'.  This is
the template manager object.  To instantiate the object, you must call
ae_template_mgr_new, as follows:

  t_ae_template_mgr mgr;

  mgr = ae_template_mgr_new();

Once the template manager is defined, you can add tokens to the manager via
the 'ae_add_tag' API:

  ae_add_tag( mgr, "one", "red" );
  ae_add_tag( mgr, "two", "blue" );

If you want support for legacy tags, simply #include "legacy_tags.h" and call
'ae_add_legacy_tags' after instantiating the template manager:

  ae_add_legacy_tags( mgr );

You can also add advanced tags, such as the dynamic-library-loading tag, via
the ae_add_tag_ex API:

  ae_add_tag_ex( mgr, ae_shared_fn_tag( "thetoken", "thelibrary",
                                        "thefunction", aparm ) );

If you have the dual array of char*'s (such as was used with the ToHTML2
function), you can add them to the template manager via 'ae_add_tags':

  ae_add_tags( mgr, tokens, values );

Lastly, you process the template like this:

  ae_process_template( mgr, "mytemplate.tem", stdout );

After processing the template, you must be sure to destroy the template
manager object:

  ae_template_mgr_done( mgr );

----------------------
Combination Method
----------------------

Sometimes you want something between these two levels of difficulty.  The
combination method also introduces a few features that are not found in either
other method, such as setting HTTP cookies to be written with the template.

As with the advanced method, you must first declare a template manager object:

  t_ae_template_mgr mgr;

Instead of using the API functions to instantiate the manager, however, you
use 'ae_init_html', which returns the instantiated object.  ae_init_html
also accepts two char* arrays, just as ToHTML2 did, as well as a 'mode'
parameter.  These values are all identical in usage to ToHTML2:

   char* tokens[] = { "one", "two", "three", NULL };
   char* values[] = { "red", "green", "blue" };

   mgr = ae_init_html( tokens, values, HTML_HEADER | HTML_LEGACY_SUPPORT );

Once the manager is instantiated, you can call any of the other TDTPP API
functions with it.  You can also set HTTP cookies via the 'ae_set_cookie'
function:

  ae_set_cookie( mgr, "name", "Nathaniel", -1 );

The last parameter is the "time-to-live" (in seconds) of the cookie.  If set
to -1, then the cookie will persist for the current browser session, which is
until the user closes their browser.  Otherwise, the cookie will live no more
than the given number of seconds from the current moment.  Thus, setting this
parameter to 0 will cause any existing cookie by that name to expire
immediately.

Note that, because cookies are written with the HTTP headers, no cookies will
be written unless you specified HTML_HEADER as one of the options passed to
ae_init_html.  Also, it is IMPORTANT TO NOTE that ae_set_cookie may only be
used with manager objects created with ae_init_html.

Once you are ready to process a template, you should do so with ae_done_html,
which writes the template and disposes of the template manager in one fell
swoop.

  ae_done_html( mgr, "mytemplate.tem" );

You should NEVER call ae_template_mgr_done on a template manager created with
ae_init_html.  If you ever need to dispose of the template manager without
processing a template, you can safely call ae_done_html and pass NULL instead
of a template name:

  ae_done_html( mgr, NULL );

This will free up the template manager, and will not process any template.  It
should be noted that this will also not print any HTTP headers (even if the
HTML_HEADER option was set).

----------------------
Standard Tags
----------------------

The following are the standard tags that are supported by the TDTPP:

  <!--%token%-->
    This is a standard replacement token.  The value of the first tag in the
    template manager with a name that matches 'token' is used to replace this
    token.

    It should be noted that the ae_shared_fn_tag_named and the
    ae_include_tag_named tags also use this same syntax, but behave as if they
    were, respectively, EXEC_SHARED and INCLUDE tags.

  <!--%IF=token=data%-->

    IF the value of 'token' is not NULL and is not the empty string, THEN
    replace this tag with 'data', otherwise replace the tag with the empty
    string.

  <!--%IF_NOT=token=data%-->

    IF the value of 'token' is NULL or is not the empty string, THEN
    replace this tag with 'data', otherwise replace the tag with the empty
    string.

  <!--%IF_EQ=token=value=data%-->
  <!--%IF_NOT_EQ=token=value=data%-->
  <!--%IF_LT=token=value=data%-->
  <!--%IF_LE=token=value=data%-->
  <!--%IF_GT=token=value=data%-->
  <!--%IF_GE=token=value=data%-->
    These tokens all print 'data' IF the value of 'token' relative to 'value'
    is the indicated comparison (EQ, NOT_EQ, LT [less than], LE [less than or
    equal to], GT [greater than], GE [greater than or equal to]).

  <!--%ENV=var%-->
    Replaces the tag with the value of the given environment variable,
    'var'.

  <!--%INCLUDE=token%-->
    If 'token' is defined, its value is treated as a filename, otherwise
    'token' is taken to be a filename.  The given file is opened, and its
    contents are used to replace this token.

  <!--%REPEAT2=source=token=delim=data%-->
    This is a fairly complex token.  The value of the token identified by
    'source' should be a sequence of values delimited by 'delim'.  'data' is
    then parsed (recursively) by TDTPP API, replacing each instance of the
    token 'token' with the next value in the 'source' sequence.  This
    continues until there are no more values in the 'source'.

    Within a REPEAT2 tag, the token <!--%ae_row_num%--> is the (1-based)
    number of the current row.  If the REPEAT2 tag is nested within another
    repeat tag, subsequent row number tokens will have a number appended to
    them, to indicate the depth of the nesting:  <!--%ae_row_num_2%-->,
    <!--%ae_row_num_3%-->, etc.

    Here's an example of a REPEAT2 tag:

      <!--%REPEAT2=source=replaceme=##=
        Values are:
          [ <!--%replaceme%-->, <!--%replaceme%-->, <!--%replaceme%--> ]
      %-->

    If the 'source' token had the following value:

      "one##two##three##four##five##six##"

    Then the REPEAT2 tag would give the following output:

      Values are:
        [ one, two, three ]
      Values are:
        [ four, five, six ]

  <!--%EXEC_SHARED=token%-->
    The value for this token is created using the ae_shared_fn_tag function.
    When this token is encountered and applied, the shared library indicated
    when the tag was created is loaded, and the given function is executed
    (passing the given parameter).  The output of the function is then
    inserted where this token was found in the template.

  <!--%EXEC=token%-->
    The value for this token is either a replace tag, or (if no matching
    tag is found), the token name itself.  The value is treated as a process
    to execute (such as the UNIX 'date' command).  The output from the process
    is used in place of the token.

----------------------
Extension Tags
----------------------
  
  These tags require that certain libraries be linked in in order to be
  usable.  You will also have to explicity add the tags to the template
  manager before you can use them (they aren't added automatically like most
  of the other tag types).

  <!--%PERL=perlcode%-->
    A perl interpreter is instantiated, and the 'perlcode' block is
    interpreted by it.  All 'valued' tags (replacement tags, and
    'cylical replacement tags' [in the REPEAT2 tag]) are added to the perl
    environment as scalar variables with the same name as the tag.  For
    instance, if the 'age' token had '35' as it's associated value:

      I am <!--%age%--> years old.
      <!--%PERL=print( "I am $age years old.\n" );%-->

    The above block would print "I am 35 years old." twice.

  <!--%RUBY=rubycode%-->
    A ruby interpreter is instantiated, and the 'rubycode' block is
    interpreted by it.  All 'valued' tags (replacement tags, and
    'cylical replacement tags' [in the REPEAT2 tag]) are added to the ruby
    environment as global variables with the same name as the tag.  For
    instance, if the 'age' token had '35' as it's associated value:

      I am <!--%age%--> years old.
      <!--%RUBY=puts "I am #{$age} years old."%-->

    The above block would print "I am 35 years old." twice.

----------------------
Extension Tags
----------------------

  The following tags are supported, if added to the template manager
  explicitly.  These tags add functionality that extends the functionality
  of the base set of tags.

  <!--%ESCAPE-JS=data%-->
    Processes 'data' by the template manager and escapes all single-quote,
    double-quote, and backslash characters, as if the data were going to be
    part of a Javascript string.  Newlines, carriage-returns, and tabs
    are also escaped.

  <!--%ESCAPE-HTML=data%-->
    Processes 'data' by the template manager and replaces all less-than,
    greater-than, and ampersand characters with HTML printable characters
    (&lt; &gt; and &amp; respectively).

----------------------
Legacy Tags
----------------------

  The following legacy tags are supported, if added to the template manager
  either via 'ae_add_legacy_tags' or by explicitly adding each tag type
  individually.  Most of them have the same functionality as one of the
  standard tags -- just a different name.

    <!--%BYU_IF=token=data%-->
    <!--%BYU_IF_NOT=token=data%-->
    <!--%BYU_IF_EQ=token=value=data%-->
    <!--%BYU_IF_NOT_EQ=token=value=data%-->
    <!--%BYU_EXEC_SHARED=token%-->
    <!--%BYU_ENV=env%-->
    <!--%BYU_EXEC=token%-->
      These tokens all duplicate the effects of the tokens of the same name
      (minus the "BYU_" prefix).  These are supported for the sake of legacy
      programs and existing templates.

    <!--%REPEAT=token=delim=data%-->
      This token is a more primitive version of the REPEAT2 tag.  Its use is
      not encouraged, as it is not as robust as the REPEAT2 tag, but for
      maintenance's sake, here's how it works:

      The 'token' value is looked for in the 'data' section, and each time it
      is found (surrounded by '%' characters, rather than the complete token
      delimiters), it is replaced by the next data value in the 'delim'
      delimited string represented by the original 'token' token.  Some of the
      other tokens were allowably nested within the REPEAT tag.  The original
      implementation did not support the <!--%ae_row_num%--> token.

