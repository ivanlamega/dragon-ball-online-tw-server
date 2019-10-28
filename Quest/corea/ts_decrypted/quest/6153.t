CNtlTSTrigger
{
	sm = 0;
	sq = 1;
	rq = 0;
	tid = 6153;
	title = 1100628;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 254;
			rm = 0;
			yeslnk = 5;

			CDboTSCheckClrQst
			{
				and = "6153;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 1100630;
				gtype = -1;
				area = 1100802;
				goal = 1100629;
				m0fz = "-3165.000000";
				m0widx = 1;
				sort = 1100406;
				stype = 32;
				m0fy = "0.000000";
				grade = -1;
				m0fx = "5742.000000";
				m0ttip = 1100628;
				rwd = 5;
				taid = 1;
				title = 1100628;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 5;
			didx0 = 120501;
			dval0 = 0;
			desc = 1100763;
			nextlnk = 255;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 3;
			ltime = -1;
			prelnk = "4;";
			usetbl = 0;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSRcvSvrEvt
			{
				id = 16220;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 1100626;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 5;
			}
			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 1100627;
			gtype = 2;
			oklnk = 2;
			area = 1100802;
			goal = 1100629;
			sort = 105;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 5;
			title = 1100628;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "4;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;";
			type = 0;
		}
	}
}

