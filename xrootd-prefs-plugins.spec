
Name:      xrootd-prefs-plugins
Version:   0.1
Release:   1%{?dist}%{?_with_xrootd_user:.xu}
Summary:   Preference plugins for the Xrootd daemon
Group:     System Environment/Daemons
License:   BSD
URL:       https://github.com/bbockelm/xrootd-prefs-plugins

# git clone http://github.com/bbockelm/xrootd-prefs-plugins.git
# cd xrootd-prefs-plugins
# git-archive master | gzip -9 > ~/rpmbuild/SOURCES/xrootd-prefs-plugins.tar.gz
Source0:   %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-root

BuildRequires: cmake
BuildRequires: xrootd-libs

%description
%{summary}

%prep
%setup -c -n %{name}

%build

cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=RelWithDebInfo
make VERBOSE=1 %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_libdir}/PrefXmi/libPrefAllowXmi.so
%{_libdir}/PrefXmi/libPrefDenyXmi.so
%{_libdir}/PrefXmi/libPrefMatchTopDomainXmi.so

%changelog
* Tue Sep 18 2012 Brian Bockelman <bbockelm@cse.unl.edu> - 0.1-1
Initial packaging of the plugins.


