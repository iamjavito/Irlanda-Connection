var gulp = require('gulp');
var sass = require('gulp-sass');
var sourcemaps = require('gulp-sourcemaps');
var clean = require('gulp-clean');
var autoprefixer = require('gulp-autoprefixer');
var concat = require('gulp-concat');
var scrape = require('website-scraper');
var browserSync = require('browser-sync');
var uglify = require('gulp-uglify');
var htmlreplace = require('gulp-html-replace');


/**
 * Website Scrapping Options
 */
const scrapeOptions = {
	urls: [
		'http://phpstack-211431-640757.cloudwaysapps.com',
	],
	directory: 'html',
	subdirectories: [
		{directory: 'js', extensions: ['.js']},
		{directory: 'css', extensions: ['.css']},
		{directory: 'json', extensions: ['.json']}
	],
	prettified : false,
	ignoreErrors: false,
	maxDepth: 0,
	recursive: true,
};

/**
 * Scrapping task
 */
gulp.task('scrape', function(){
	scrape(scrapeOptions, (error, result) => {
		console.log("Webpages succesfully downloaded");

		// Run Browser Sync after Website Scrape is completed
		return gulp.series(
      'replace',
      'sass',
      'javascript',
      'browser-sync'
		)();

	}).catch((err) => {
		console.log("An error ocurred", err);
	});
});

/**
 * Delete current HTML folder to avoid overrides and errors
 * also, replace all css and js with local files
 */
gulp.task('del', function() {
  return gulp.src('html', {read: false, allowEmpty: true})
    .pipe(clean());
});

/**
 * Replace origins CSS and JS with local compiled one
 */
gulp.task('replace', function() {
  return gulp.src('html/**')
      .pipe(htmlreplace({
          'css': 'css/irlanda-connection.styles.css',
          'js': 'js/irlanda-connection.behaviors.js'
      }))
      .pipe(gulp.dest('html'));
});

gulp.task('build-prod', function () {
  return gulp.src('./html/**')
    .pipe(gulp.dest('./html'));
});

/**
 * 
 * SCSS Compiler
 */
gulp.task('sass', function () {
  return gulp.src('./sass/*.scss')
      .pipe(sourcemaps.init())
      .pipe(sass({outputStyle: 'compressed'}).on('error', sass.logError))
      .pipe(sourcemaps.write('./maps'))
      .pipe(gulp.dest('./css/'))
      .pipe(gulp.dest('./html/css/'))
      .pipe(browserSync.stream())
});

/**
 * Javascript Uglify
 */
gulp.task('javascript', function() {
    return gulp.src([
		'./js/irlanda-connection.behaviors.js',
		
        ])
    .pipe(uglify())
    .on('error', function(error) {
        console.log(error);
      })
    .pipe(concat('bundle.js'))
    .pipe(gulp.dest('./js/min'))
    .pipe(gulp.dest('./html/js/'))
    .pipe(browserSync.stream())
});


/**
 * Static server
 */
gulp.task('browser-sync', function() {
  browserSync.init({
      server: {
        baseDir: "./html"
      }
  });
  // Run Sass after Browser-sync is completed
  return gulp.series(
    'build-prod',
    gulp.parallel('sass', 'javascript')
  )();
});

/**
 * Watcher
 */
gulp.task('watching', function () {
  gulp.watch(['./sass/**/*.scss'], gulp.series('sass'));
  gulp.watch(['./js/irlanda-connection.behaviors.js'], gulp.series('javascript'));
});

/**
 * Default deployer
 */
gulp.task('default', 
        gulp.series('del', 
        gulp.parallel('scrape', 'watching'),
        gulp.series('build-prod')
    ),
);    
