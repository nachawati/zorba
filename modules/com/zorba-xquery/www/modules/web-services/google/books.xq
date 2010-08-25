(:~
 : Google Books Services Module
 : This module wraps a few of the Google Book Search APIs listed on <a href="http://code.google.com/apis/books/" target="_blank">http://code.google.com/apis/books/</a>
 : @author Stephanie Russell
 : @version 1.0
 :)

module namespace google = 'http://www.zorba-xquery.com/modules/web-services/google/books';
import module namespace http = "http://expath.org/ns/http-client";
(:~
 : Use err module functions for throwing errors.
 :)
import module namespace err="http://www.zorba-xquery.com/modules/web-services/google/errors-books";

(:~
 : This function returns the xml response of a book search.
 : @param $book string query for book search
 : @param $start integer describing where to start the results
 : @param $max integer describing where to end the results
 : @return xml response describing book results close to query string $book.
 :)
declare function google:book-search-xml($book as xs:string, $start as xs:integer?, $max as xs:integer?)
{
  let $query := fn:replace(fn:replace($book, "NOT ", "-"), " ","+")
  let $href := concat("http://books.google.com/books/feeds/volumes?q=",$query,
    if (empty($start))
    then ""
    else concat("&amp;start-index=",$start),
    if(empty($max))
    then ""
    else concat("&amp;max-results=",$max))
  return http:read($href)[2]
};

(:~
 : This function returns the ISBN (and other identifying numbers) for a book.
 : @param $book string query for book search
 : @param $start integer describing where to start the results
 : @param $max integer describing where to end the results
 : @return response containing ISBNs for book query results close to query string $book.
 :)
declare function google:ISBN($book as xs:string, $start as xs:integer?, $max as xs:integer?) as xs:string+
{
  let $response := google:book-search-xml($book, $start, $max)
  return
    if(xs:string($response//*:totalResults) eq "0")
    then error($err:GS002, concat("No book results found containing: ", $book))
    else
      for $isbn in $response//*:identifier/data(.)
      return ($isbn, "&#xA;")
};