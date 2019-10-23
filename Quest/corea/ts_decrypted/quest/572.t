CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 572;
	title = 57202;

	CNtlTSGroup
	{
		gid = 0;

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
			stdiag = 57207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4141107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 28;
				minlvl = 20;
			}
			CDboTSCheckClrQst
			{
				and = "552;";
			}
		}
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 57214;
			nextlnk = 101;
			rwdtbl = 57201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4141107;
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
				conv = 57209;
				ctype = 1;
				idx = 4141107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 57208;
				m1fx = "6754.000000";
				area = 57201;
				goal = 57204;
				m0fz = "-110.000000";
				m0widx = 7;
				m1fy = "0.000000";
				m1ttip = 57216;
				sort = 57205;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-4270.000000";
				grade = 132203;
				m0fx = "107.000000";
				m0ttip = 57215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 57202;
				gtype = 4;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 3212110;
				cnt0 = 4;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 57208;
			gtype = 4;
			oklnk = 2;
			area = 57201;
			goal = 57204;
			sort = 57205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 57202;
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

