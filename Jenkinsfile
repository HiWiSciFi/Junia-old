pipeline {
	agent any
	stages {
		stage('Build') {
			steps {
				sh 'echo "Building..."'
				sh 'chmod +x scripts/linux_build.sh'
				sh 'cd scripts && ./linux_build.sh'
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
