#!groovy
node{
    sh "pwd"
    sh "ls"
	stage('Build'){
	    dir ("_bld"){
		  sh 'cmake ..' //First Step
		  sh 'make'
	    }
	}
}