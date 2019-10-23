CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6023;
	title = 602302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 602309;
				ctype = 1;
				idx = 3332301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 602308;
				gtype = 0;
				area = 602301;
				goal = 602304;
				grade = -1;
				rwd = 100;
				sort = 602305;
				stype = 8;
				taid = 1;
				title = 602302;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 602307;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3332301;
			}
			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6022;";
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 602314;
			nextlnk = 253;
			rwdtbl = 602301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3181301;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 602308;
			gtype = 0;
			oklnk = 2;
			area = 602301;
			goal = 602304;
			sort = 602305;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 602302;
		}
	}
}

