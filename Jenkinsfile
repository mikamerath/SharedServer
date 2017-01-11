#!groovy
node{
	git credentialsId: '7057a6d4-0dbd-4c32-88e0-8e294bfce51e', url: 'https://github.com/michaelkamerath/SharedServer/'
	stage('Build'){
		sh 'cmake' //First Step
		sh 'make'
	}
}