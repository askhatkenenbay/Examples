<!DOCTYPE html>
<html>
<title>Serious Science</title>
<link rel="icon" type="image/ico" href="https://www.atlassian.design/server/images/iconography/Icon_branches_example_24_2x.png" />
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Karma">
<style>
    body,h1,h2,h3,h4,h5,h6 {font-family: "Karma", sans-serif}
    .w3-bar-block .w3-bar-item {padding:20px}
</style>
<body>

<!-- Sidebar (hidden by default) -->
<nav class="w3-sidebar w3-bar-block w3-card w3-top w3-xlarge w3-animate-left" style="display:none;z-index:2;width:40%;min-width:300px" id="mySidebar">
    <a href="javascript:void(0)" onclick="w3_close()"
       class="w3-bar-item w3-button">Close Menu</a>
    <a href="#food" onclick="w3_close()" class="w3-bar-item w3-button">Courses</a>
    <a href="#about" onclick="w3_close()" class="w3-bar-item w3-button">About</a>
</nav>

<!-- Top menu -->
<div class="w3-top">
    <div class="w3-white w3-xlarge" style="max-width:1200px;margin:auto">
        <div class="w3-button w3-padding-16 w3-left" onclick="w3_open()">Menu</div>
        <div class="w3-right w3-padding-16">Cart</div>
        <div class="w3-center w3-padding-16">Courses</div>
    </div>
</div>

<!-- !PAGE CONTENT! -->
<div class="w3-main w3-content w3-padding" style="max-width:1200px;margin-top:100px">

    <!-- First Photo Grid-->
    <div class="w3-row-padding w3-padding-16 w3-center" id="food">
        <div class="w3-quarter">
            <img src="https://aptonic.com/blog/wp-content/uploads/2015/08/python-logo.png" alt="Python" style="width:100%">
            <h3>Python course for beginners</h3>
            <p>Python is an interpreted, high-level, general-purpose programming language.</p>
        </div>
        <div class="w3-quarter">
            <img src="https://ih1.redbubble.net/image.418233732.0994/flat,1000x1000,075,f.u1.jpg" alt="Java Development" style="width:100%">
            <h3>Java Development Training in EPAM</h3>
            <p>EPAM is a global provider of software engineering and IT consulting services headquartered in Newtown, Pennsylvania, United States.</p>
        </div>
        <div class="w3-quarter">
            <img src="https://www.xtremeinfinity.com/wp-content/uploads/2015/12/PHP-7.png" alt="PHP" style="width:100%">
            <h3>PHP course</h3>
            <p>PHP: Hypertext Preprocessor is a general-purpose programming language originally designed for web development. </p>

        </div>
        <div class="w3-quarter">
            <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/34/Android_Studio_icon.svg/1024px-Android_Studio_icon.svg.png" alt="Android Studio" style="width:100%">
            <h3>Learn Android studio today</h3>
            <p>Android Studio is the official integrated development environment for Google's Android operating system, built on JetBrains' IntelliJ IDEA software and designed specifically for Android development.</p>
        </div>
    </div>

    <!-- Second Photo Grid-->
    <div class="w3-row-padding w3-padding-16 w3-center">
        <div class="w3-quarter">
            <img src="http://www.softcrayons.com/Blog/wp-content/uploads/2019/06/c.jpg" alt="C++" style="width:100%">
            <h3>C++ course</h3>
            <p>C++ is a general-purpose programming language created by Bjarne Stroustrup as an extension of the C programming language, or "C with Classes</p>
        </div>
        <div class="w3-quarter">
            <img src="https://ih0.redbubble.net/image.374103903.2990/ap,550x550,12x12,1,transparent,t.png" alt="Kotlin" style="width:100%">
            <h3>Kotlin course</h3>
            <p>Kotlin is a cross-platform, statically typed, general-purpose programming language with type inference.</p>
        </div>
        <div class="w3-quarter">
            <img src="https://ctl.s6img.com/society6/img/dh59Kgf2jS0VOBBj_6ELGHknDEk/w_700/prints/~artwork/s6-original-art-uploads/society6/uploads/misc/6668936326d74c3a8bf31df3bc0430eb/~~/c-logo-for-csharp-developers-visual-studio-prints.jpg" alt="C#" style="width:100%">
            <h3>C# course</h3>
            <p>C# is a general-purpose, multi-paradigm programming language encompassing strong typing, lexically scoped, imperative, declarative, functional, generic, object-oriented, and component-oriented programming disciplines.</p>
        </div>
        <div class="w3-quarter">
            <img src="https://b.kisscc0.com/20180815/zlq/kisscc0-computer-icons-logo-brand-javascript-angle-js-5b741783856f77.0690615715343348515466.png" alt="Javascript" style="width:100%">
            <h3>Javascript course</h3>
            <p>JavaScript, often abbreviated as JS, is a high-level, interpreted programming language that conforms to the ECMAScript specification. </p>
        </div>
    </div>

    <hr id="about">

    <!-- About Section -->
    <div class="w3-container w3-padding-32 w3-center">
        <h3>About Company</h3><br>
        <img src="https://cdn.dribbble.com/users/69156/screenshots/1088446/serious_science_dribbble.png" alt="Serious Science" class="w3-image" style="display:block;margin:auto" width="800" height="533">
        <div class="w3-padding-32">
            <h4><b>Making Better Future</b></h4>
            <p>Serious Science is an independent, non-profit, non-governmental project whose main mission is to spread knowledge and share the greatest advances in various realms of academia with our readers. </p>
        </div>
    </div>
    <hr>



    <!-- End page content -->
</div>

<script>
    // Script to open and close sidebar
    function w3_open() {
        document.getElementById("mySidebar").style.display = "block";
    }

    function w3_close() {
        document.getElementById("mySidebar").style.display = "none";
    }
</script>

</body>
</html>
