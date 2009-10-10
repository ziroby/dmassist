package com.ziroby.dmassist.jni;

/**
 * A general purpose option JNI extension library. Missing libraries do not
 * cause an exception, and methods can be used to determine if the library is
 * loaded or not.
 * 
 * @author Ron Romero
 * 
 */
public class JniLibrary {

    private static boolean libraryLoaded = false;
    private static UnsatisfiedLinkError exception = null;

    /**
     * Tries to load the given JNI library. Will NOT throw an exception. Rather,
     * the {@link #isLibraryLoaded()} can be used to determine if library
     * loading succeeded, and {@link #getException()} can be used to determine
     * the exception thrown if not.  If library loading succeeded, JNI classes
     * in the library may now be used. 
     * 
     * @param libraryName
     *            The name of the library to load. Do not include extensions or
     *            "lib" prefixes.
     */
    protected static void tryLoadLibrary(final String libraryName) {
        try
        {
            System.loadLibrary(libraryName);
            libraryLoaded = true;
        }
        catch (UnsatisfiedLinkError e)
        {
            exception = e;
            libraryLoaded = false;
        }
    }
    
    /**
     * Ensured that the library is loaded.  If not, throws the exception
     * that was generated when the library was initially loaded.
     */
    protected static void checkLibraryLoaded()
    {
        if (!isLibraryLoaded())
        {
            throw exception;
        }
    }

    /**
     * If we failed loading the library, gives the exception thrown.
     */
    public static UnsatisfiedLinkError getException() {
        return exception;
    }

    /**
     * Did we successfully load the link library?
     * 
     */
    public static boolean isLibraryLoaded() {
        return libraryLoaded;
    }

    public JniLibrary() {
        super();
    }

}
