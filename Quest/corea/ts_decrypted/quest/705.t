CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 705;
	title = 70502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 70507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 32;
				minlvl = 24;
			}
			CDboTSCheckClrQst
			{
				and = "680;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 70509;
				ctype = 1;
				idx = 3031101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 70508;
				m1fx = "5811.000000";
				m2fz = "2239.000000";
				m1fy = "0.000000";
				sort = 70505;
				m2widx = 1;
				grade = 132203;
				m0fx = "5785.100098";
				m0ttip = 70515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 70502;
				gtype = 2;
				area = 70501;
				goal = 70504;
				m0fz = "2241.699951";
				m0widx = 1;
				m1ttip = 70516;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "-95.000000";
				m1fz = "2111.000000";
				m2fx = "5894.000000";
				m2ttip = 70517;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 9;
				eitype = 0;
				idx0 = 8911101;
				cnt0 = 9;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 8913200;
				taid = 3;
				esctype = 0;
				idx2 = 8911200;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 70514;
			nextlnk = 101;
			rwdtbl = 70501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3032103;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 70508;
			gtype = 2;
			oklnk = 2;
			area = 70501;
			goal = 70504;
			sort = 70505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 70502;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

