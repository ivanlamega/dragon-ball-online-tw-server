CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6003;
	title = 600302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActNPCConv
			{
				conv = 600320;
				ctype = 1;
				idx = 2972101;
				taid = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSClickNPC
			{
				npcidx = 2972101;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
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
			stdiag = 600307;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6002;";
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 600314;
			nextlnk = 253;
			rwdtbl = 600301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3551101;
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
				conv = 600309;
				ctype = 1;
				idx = 3031101;
				taid = 1;
			}
			CDboTSActRegQInfo
			{
				cont = 600308;
				gtype = 1;
				area = 600301;
				goal = 600304;
				grade = -1;
				rwd = 100;
				sort = 600305;
				stype = 8;
				taid = 2;
				title = 600302;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 600308;
			gtype = 1;
			oklnk = 2;
			area = 600301;
			goal = 600304;
			sort = 600305;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 600302;
		}
	}
}

