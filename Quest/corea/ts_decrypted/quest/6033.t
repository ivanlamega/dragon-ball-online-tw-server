CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6033;
	title = 603302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 603308;
			gtype = 3;
			oklnk = 2;
			area = 603301;
			goal = 603304;
			sort = 603305;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 603302;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "4;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 603307;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 16;
			}
			CDboTSClickNPC
			{
				npcidx = 4751104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6032;";
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 253;
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
			desc = 603314;
			nextlnk = 4;
			rwdtbl = 603301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511101;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 603309;
				ctype = 1;
				idx = 4751104;
				taid = 1;
			}
			CDboTSActRegQInfo
			{
				cont = 603308;
				gtype = 3;
				area = 603301;
				goal = 603304;
				m0fz = "4973.680176";
				m0widx = 1;
				sort = 603305;
				stype = 8;
				m0fy = "0.000000";
				grade = -1;
				m0fx = "5722.669922";
				m0ttip = 603315;
				rwd = 100;
				taid = 3;
				title = 603302;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 6631200;
				cnt0 = 10;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
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
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
			type = 0;
		}
	}
}

