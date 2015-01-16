// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.cronet_test_apk.urlconnection;

import android.test.suitebuilder.annotation.SmallTest;

import org.chromium.base.test.util.Feature;
import org.chromium.cronet_test_apk.CronetTestActivity;
import org.chromium.cronet_test_apk.CronetTestBase;
import org.chromium.cronet_test_apk.UploadTestServer;
import org.chromium.net.UrlRequestException;

import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Basic tests of Cronet's HttpURLConnection implementation.
 * Tests annotated with {@code CompareDefaultWithCronet} will run once with the
 * default HttpURLConnection implementation and then with Cronet's
 * HttpURLConnection implementation. Tests annotated with
 * {@code OnlyRunCronetHttpURLConnection} only run Cronet's implementation.
 * See {@link CronetTestBase#runTest()} for details.
 */
public class CronetHttpURLConnectionTest extends CronetTestBase {
    private CronetTestActivity mActivity;

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        mActivity = launchCronetTestApp();
        assertTrue(UploadTestServer.startUploadTestServer(
                getInstrumentation().getTargetContext()));
    }

    @Override
    protected void tearDown() throws Exception {
        UploadTestServer.shutdownUploadTestServer();
        super.tearDown();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testBasicGet() throws Exception {
        URL url = new URL(UploadTestServer.getEchoMethodURL());
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        assertEquals(200, urlConnection.getResponseCode());
        assertEquals("OK", urlConnection.getResponseMessage());
        assertEquals("GET", getResponseAsString(urlConnection));
        urlConnection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testNotFoundURLRequest() throws Exception {
        URL url = new URL(UploadTestServer.getFileURL("/notfound.html"));
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        assertEquals(404, urlConnection.getResponseCode());
        assertEquals("Not Found", urlConnection.getResponseMessage());
        try {
            urlConnection.getInputStream();
            fail();
        } catch (FileNotFoundException e) {
            // Expected.
        }
        InputStream errorStream = urlConnection.getErrorStream();
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        int byteRead;
        while ((byteRead = errorStream.read()) != -1) {
            out.write(byteRead);
        }
        assertEquals("<!DOCTYPE html>\n<html>\n<head>\n"
                + "<title>Not found</title>\n<p>Test page loaded.</p>\n"
                + "</head>\n</html>\n",
                out.toString());
        urlConnection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testServerNotAvailable() throws Exception {
        URL url = new URL(UploadTestServer.getFileURL("/success.txt"));
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        assertEquals("this is a text file\n",
                getResponseAsString(urlConnection));
        // After shutting down the server, the server should not be handling
        // new requests.
        UploadTestServer.shutdownUploadTestServer();
        HttpURLConnection secondConnection =
                (HttpURLConnection) url.openConnection();
        try {
            secondConnection.connect();
            fail();
        } catch (IOException e) {
            assertTrue(e instanceof java.net.ConnectException
                    || e instanceof UrlRequestException);
            assertTrue((e.getMessage().contains("ECONNREFUSED")
                    || e.getMessage().contains("net::ERR_CONNECTION_REFUSED")));
        }
        checkExceptionsAreThrown(secondConnection);
        // Starts the server to avoid crashing on shutdown in tearDown().
        assertTrue(UploadTestServer.startUploadTestServer(
                getInstrumentation().getTargetContext()));
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testBadIP() throws Exception {
        URL url = new URL("http://0.0.0.0/");
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        try {
            urlConnection.connect();
            fail();
        } catch (IOException e) {
            assertTrue(e instanceof java.net.ConnectException
                    || e instanceof UrlRequestException);
            assertTrue((e.getMessage().contains("ECONNREFUSED")
                    || e.getMessage().contains("net::ERR_CONNECTION_REFUSED")));
        }
        checkExceptionsAreThrown(urlConnection);
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testBadHostname() throws Exception {
        URL url = new URL("http://this-weird-host-name-does-not-exist/");
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        try {
            urlConnection.connect();
            fail();
        } catch (java.net.UnknownHostException e) {
            // Expected.
        } catch (UrlRequestException e) {
            // Expected.
        }
        checkExceptionsAreThrown(urlConnection);
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testBadScheme() throws Exception {
        try {
            URL url = new URL("flying://goat");
            fail();
        } catch (MalformedURLException e) {
            // Expected.
        }
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testDisconnectBeforeConnectionIsMade() throws Exception {
        URL url = new URL(UploadTestServer.getEchoMethodURL());
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        // Close connection before connection is made has no effect.
        // Default implementation passes this test.
        urlConnection.disconnect();
        assertEquals(200, urlConnection.getResponseCode());
        assertEquals("OK", urlConnection.getResponseMessage());
        assertEquals("GET", getResponseAsString(urlConnection));
    }

    @SmallTest
    @Feature({"Cronet"})
    // TODO(xunjieli): Currently the wrapper does not throw an exception.
    // Need to change the behavior.
    // @CompareDefaultWithCronet
    public void testDisconnectAfterConnectionIsMade() throws Exception {
        URL url = new URL(UploadTestServer.getEchoMethodURL());
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        // Close connection before connection is made has no effect.
        urlConnection.connect();
        urlConnection.disconnect();
        try {
            urlConnection.getResponseCode();
            fail();
        } catch (Exception e) {
            // Ignored.
        }
        try {
            InputStream in = urlConnection.getInputStream();
            fail();
        } catch (Exception e) {
            // Ignored.
        }
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testAddRequestProperty() throws Exception {
        URL url = new URL(UploadTestServer.getEchoAllHeadersURL());
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.addRequestProperty("foo-header", "foo");
        connection.addRequestProperty("bar-header", "bar");

        // Before connection is made, check request headers are set.
        Map<String, List<String>> requestHeadersMap =
                connection.getRequestProperties();
        List<String> fooValues = requestHeadersMap.get("foo-header");
        assertEquals(1, fooValues.size());
        assertEquals("foo", fooValues.get(0));
        assertEquals("foo", connection.getRequestProperty("foo-header"));
        List<String> barValues = requestHeadersMap.get("bar-header");
        assertEquals(1, barValues.size());
        assertEquals("bar", barValues.get(0));
        assertEquals("bar", connection.getRequestProperty("bar-header"));

        // Check the request headers echoed back by the server.
        assertEquals(200, connection.getResponseCode());
        assertEquals("OK", connection.getResponseMessage());
        String headers = getResponseAsString(connection);
        List<String> fooHeaderValues =
                getRequestHeaderValues(headers, "foo-header");
        List<String> barHeaderValues =
                getRequestHeaderValues(headers, "bar-header");
        assertEquals(1, fooHeaderValues.size());
        assertEquals("foo", fooHeaderValues.get(0));
        assertEquals(1, fooHeaderValues.size());
        assertEquals("bar", barHeaderValues.get(0));

        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @OnlyRunCronetHttpURLConnection
    public void testAddRequestPropertyWithSameKey() throws Exception {
        URL url = new URL(UploadTestServer.getEchoAllHeadersURL());
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        urlConnection.addRequestProperty("header-name", "value1");
        try {
            urlConnection.addRequestProperty("header-Name", "value2");
            fail();
        } catch (UnsupportedOperationException e) {
            assertEquals(e.getMessage(),
                    "Cannot add multiple headers of the same key. "
                    + "crbug.com/432719.");
        }
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testSetRequestPropertyWithSameKey() throws Exception {
        URL url = new URL(UploadTestServer.getEchoAllHeadersURL());
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        // The test always sets and retrieves one header with the same
        // capitalization, and the other header with slightly different
        // capitalization.
        conn.setRequestProperty("same-capitalization", "yo");
        conn.setRequestProperty("diFFerent-cApitalization", "foo");
        Map<String, List<String>> headersMap = conn.getRequestProperties();
        List<String>  values1 = headersMap.get("same-capitalization");
        assertEquals(1, values1.size());
        assertEquals("yo", values1.get(0));
        assertEquals("yo", conn.getRequestProperty("same-capitalization"));

        List<String> values2 = headersMap.get("different-capitalization");
        assertEquals(1, values2.size());
        assertEquals("foo", values2.get(0));
        assertEquals("foo",
                conn.getRequestProperty("Different-capitalization"));

        // Check request header is updated.
        conn.setRequestProperty("same-capitalization", "hi");
        conn.setRequestProperty("different-Capitalization", "bar");
        Map<String, List<String>> newHeadersMap = conn.getRequestProperties();
        List<String> newValues1 = newHeadersMap.get("same-capitalization");
        assertEquals(1, newValues1.size());
        assertEquals("hi", newValues1.get(0));
        assertEquals("hi", conn.getRequestProperty("same-capitalization"));

        List<String> newValues2 = newHeadersMap.get("differENT-capitalization");
        assertEquals(1, newValues2.size());
        assertEquals("bar", newValues2.get(0));
        assertEquals("bar",
                conn.getRequestProperty("different-capitalization"));

        // Check the request headers echoed back by the server.
        assertEquals(200, conn.getResponseCode());
        assertEquals("OK", conn.getResponseMessage());
        String headers = getResponseAsString(conn);
        List<String> actualValues1 =
                getRequestHeaderValues(headers, "same-capitalization");
        assertEquals(1, actualValues1.size());
        assertEquals("hi", actualValues1.get(0));
        List<String> actualValues2 =
                getRequestHeaderValues(headers, "different-Capitalization");
        assertEquals(1, actualValues2.size());
        assertEquals("bar", actualValues2.get(0));
        conn.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testAddAndSetRequestPropertyWithSameKey() throws Exception {
        URL url = new URL(UploadTestServer.getEchoAllHeadersURL());
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.addRequestProperty("header-name", "value1");
        connection.setRequestProperty("Header-nAme", "value2");

        // Before connection is made, check request headers are set.
        assertEquals("value2", connection.getRequestProperty("header-namE"));
        Map<String, List<String>> requestHeadersMap =
                connection.getRequestProperties();
        assertEquals(1, requestHeadersMap.get("HeAder-name").size());
        assertEquals("value2", requestHeadersMap.get("HeAder-name").get(0));

        // Check the request headers echoed back by the server.
        assertEquals(200, connection.getResponseCode());
        assertEquals("OK", connection.getResponseMessage());
        String headers = getResponseAsString(connection);
        List<String> actualValues =
                getRequestHeaderValues(headers, "Header-nAme");
        assertEquals(1, actualValues.size());
        assertEquals("value2", actualValues.get(0));
        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testAddSetRequestPropertyAfterConnected() throws Exception {
        URL url = new URL(UploadTestServer.getEchoAllHeadersURL());
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.addRequestProperty("header-name", "value");
        assertEquals(200, connection.getResponseCode());
        assertEquals("OK", connection.getResponseMessage());
        try {
            connection.setRequestProperty("foo", "bar");
            fail();
        } catch (IllegalStateException e) {
            // Expected.
        }
        try {
            connection.addRequestProperty("foo", "bar");
            fail();
        } catch (IllegalStateException e) {
            // Expected.
        }
        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testGetRequestPropertyAfterConnected() throws Exception {
        URL url = new URL(UploadTestServer.getEchoAllHeadersURL());
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.addRequestProperty("header-name", "value");
        assertEquals(200, connection.getResponseCode());
        assertEquals("OK", connection.getResponseMessage());

        try {
            connection.getRequestProperties();
            fail();
        } catch (IllegalStateException e) {
            // Expected.
        }

        // Default implementation allows querying a particular request property.
        try {
            assertEquals("value", connection.getRequestProperty("header-name"));
        } catch (IllegalStateException e) {
            fail();
        }
        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testGetRequestPropertiesUnmodifiable() throws Exception {
        URL url = new URL(UploadTestServer.getEchoAllHeadersURL());
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.addRequestProperty("header-name", "value");
        Map<String, List<String>> headers = connection.getRequestProperties();
        try {
            headers.put("foo", Arrays.asList("v1", "v2"));
            fail();
        } catch (UnsupportedOperationException e) {
            // Expected.
        }

        List<String> values = headers.get("header-name");
        try {
            values.add("v3");
            fail();
        } catch (UnsupportedOperationException e) {
            // Expected.
        }

        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testInputStreamReadOneByte() throws Exception {
        String testInputString = "this is a really long header";
        URL url = new URL(UploadTestServer.getEchoHeaderURL("foo"));
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        urlConnection.addRequestProperty("foo", testInputString);
        assertEquals(200, urlConnection.getResponseCode());
        assertEquals("OK", urlConnection.getResponseMessage());
        InputStream in = urlConnection.getInputStream();
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        int b;
        while ((b = in.read()) != -1) {
            out.write(b);
        }
        urlConnection.disconnect();
        assertTrue(Arrays.equals(
                testInputString.getBytes(), out.toByteArray()));
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testInputStreamReadMoreBytesThanAvailable() throws Exception {
        String testInputString = "this is a really long header";
        byte[] testInputBytes = testInputString.getBytes();
        URL url = new URL(UploadTestServer.getEchoHeaderURL("foo"));
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        urlConnection.addRequestProperty("foo", testInputString);
        assertEquals(200, urlConnection.getResponseCode());
        assertEquals("OK", urlConnection.getResponseMessage());
        InputStream in = urlConnection.getInputStream();
        byte[] actualOutput = new byte[testInputBytes.length + 256];
        int bytesRead = in.read(actualOutput, 0, actualOutput.length);
        byte[] readSomeMore = new byte[10];
        int bytesReadBeyondAvailable  = in.read(readSomeMore, 0, 10);
        urlConnection.disconnect();
        assertEquals(testInputBytes.length, bytesRead);
        assertEquals(-1, bytesReadBeyondAvailable);
        for (int i = 0; i < bytesRead; i++) {
            assertEquals(testInputBytes[i], actualOutput[i]);
        }
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testInputStreamReadExactBytesAvailable() throws Exception {
        String testInputString = "this is a really long header";
        byte[] testInputBytes = testInputString.getBytes();
        URL url = new URL(UploadTestServer.getEchoHeaderURL("foo"));
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        urlConnection.addRequestProperty("foo", testInputString);
        assertEquals(200, urlConnection.getResponseCode());
        assertEquals("OK", urlConnection.getResponseMessage());
        InputStream in = urlConnection.getInputStream();
        byte[] actualOutput = new byte[testInputBytes.length];
        int bytesRead = in.read(actualOutput, 0, actualOutput.length);
        urlConnection.disconnect();
        assertEquals(testInputBytes.length, bytesRead);
        assertTrue(Arrays.equals(testInputBytes, actualOutput));
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testInputStreamReadLessBytesThanAvailable() throws Exception {
        String testInputString = "this is a really long header";
        byte[] testInputBytes = testInputString.getBytes();
        URL url = new URL(UploadTestServer.getEchoHeaderURL("foo"));
        HttpURLConnection urlConnection =
                (HttpURLConnection) url.openConnection();
        urlConnection.addRequestProperty("foo", testInputString);
        assertEquals(200, urlConnection.getResponseCode());
        assertEquals("OK", urlConnection.getResponseMessage());
        InputStream in = urlConnection.getInputStream();
        byte[] firstPart = new byte[testInputBytes.length - 10];
        int firstBytesRead = in.read(firstPart, 0, testInputBytes.length - 10);
        byte[] secondPart = new byte[10];
        int secondBytesRead = in.read(secondPart, 0, 10);
        assertEquals(testInputBytes.length - 10, firstBytesRead);
        assertEquals(10, secondBytesRead);
        for (int i = 0; i < firstPart.length; i++) {
            assertEquals(testInputBytes[i], firstPart[i]);
        }
        for (int i = 0; i < secondPart.length; i++) {
            assertEquals(testInputBytes[firstPart.length + i], secondPart[i]);
        }
        urlConnection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testFollowRedirects() throws Exception {
        URL url = new URL(UploadTestServer.getFileURL("/redirect.html"));
        HttpURLConnection connection =
                (HttpURLConnection) url.openConnection();
        connection.setInstanceFollowRedirects(true);
        assertEquals(200, connection.getResponseCode());
        assertEquals("OK", connection.getResponseMessage());
        assertEquals(UploadTestServer.getFileURL("/success.txt"),
                connection.getURL().toString());
        assertEquals("this is a text file\n", getResponseAsString(connection));
        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testDisableRedirects() throws Exception {
        URL url = new URL(UploadTestServer.getFileURL("/redirect.html"));
        HttpURLConnection connection =
                (HttpURLConnection) url.openConnection();
        connection.setInstanceFollowRedirects(false);
        assertEquals(302, connection.getResponseCode());
        assertEquals("Found", connection.getResponseMessage());
        assertEquals(UploadTestServer.getFileURL("/redirect.html"),
                connection.getURL().toString());
        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testDisableRedirectsGlobal() throws Exception {
        HttpURLConnection.setFollowRedirects(false);
        URL url = new URL(UploadTestServer.getFileURL("/redirect.html"));
        HttpURLConnection connection =
                (HttpURLConnection) url.openConnection();
        assertEquals(302, connection.getResponseCode());
        assertEquals("Found", connection.getResponseMessage());
        assertEquals(UploadTestServer.getFileURL("/redirect.html"),
                connection.getURL().toString());
        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @CompareDefaultWithCronet
    public void testDisableRedirectsGlobalAfterConnectionIsCreated()
            throws Exception {
        HttpURLConnection.setFollowRedirects(true);
        URL url = new URL(UploadTestServer.getFileURL("/redirect.html"));
        HttpURLConnection connection =
                (HttpURLConnection) url.openConnection();
        // Disabling redirects globally after creating the HttpURLConnection
        // object should have no effect on the request.
        HttpURLConnection.setFollowRedirects(false);
        assertEquals(200, connection.getResponseCode());
        assertEquals("OK", connection.getResponseMessage());
        assertEquals(UploadTestServer.getFileURL("/success.txt"),
                connection.getURL().toString());
        assertEquals("this is a text file\n", getResponseAsString(connection));
        connection.disconnect();
    }

    @SmallTest
    @Feature({"Cronet"})
    @OnlyRunCronetHttpURLConnection
    // Cronet does not support reading response body of a 302 response.
    public void testDisableRedirectsTryReadBody() throws Exception {
        URL url = new URL(UploadTestServer.getFileURL("/redirect.html"));
        HttpURLConnection connection =
                (HttpURLConnection) url.openConnection();
        connection.setInstanceFollowRedirects(false);
        try {
            connection.getInputStream();
            fail();
        } catch (IOException e) {
            // Expected.
        }
        assertNull(connection.getErrorStream());
        connection.disconnect();
    }

    private void checkExceptionsAreThrown(HttpURLConnection connection)
            throws Exception {
        try {
            connection.connect();
            fail();
        } catch (IOException e) {
            // Expected.
        }

        try {
            connection.getInputStream();
            fail();
        } catch (IOException e) {
            // Expected.
        }

        try {
            connection.getResponseCode();
            fail();
        } catch (IOException e) {
            // Expected.
        }

        try {
            connection.getResponseMessage();
            fail();
        } catch (IOException e) {
            // Expected.
        }

        // getErrorStream() does not have a throw clause, it returns null if
        // there's an exception.
        InputStream errorStream = connection.getErrorStream();
        assertNull(errorStream);
    }

    /**
     * Helper method to extract response body as a string for testing.
     */
    private String getResponseAsString(HttpURLConnection connection)
            throws Exception {
        InputStream in = connection.getInputStream();
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        int b;
        while ((b = in.read()) != -1) {
            out.write(b);
        }
        return out.toString();
    }

    /**
     * Helper method to extract a list of header values with the give header
     * name.
     */
    private List<String> getRequestHeaderValues(String allHeaders,
            String headerName) {
        Pattern pattern = Pattern.compile(headerName + ":\\s(.*)\\r\\n");
        Matcher matcher = pattern.matcher(allHeaders);
        List<String> headerValues = new ArrayList<String>();
        while (matcher.find()) {
            headerValues.add(matcher.group(1));
        }
        return headerValues;
    }
}
