pipeline {
	agent any
	stages {
		stage('Build') {
			steps {
				sh 'echo "Building..."'
				sh 'chmod +x scripts/linux-build.sh'
				sh 'cd scripts && linux-build.sh'
				archiveArtifacts artifacts: 'build/*', fingerprint: true
			}
		}
		stage('Test') {
			steps {
				sh 'echo "Running..."'
			}
		}
	}
}
